#!/bin/bash

readonly IMAGE="buttovvski/httpserver"
readonly CONTAINERS=("service1" "service2" "service3")
declare -A CORE_ASSIGNMENTS=([service1]=0 [service2]=1 [service3]=2)

log_message() {
    echo "[$(date +'%Y-%m-%d %H:%M:%S')] $1"
}

check_container_status() {
    local container=$1
    if docker ps --format '{{.Names}}' | grep -q "$container"; then
        echo "running"
    elif docker ps -a --format '{{.Names}}' | grep -q "$container"; then
        echo "exists"
    else
        echo "none"
    fi
}

get_cpu_usage() {
    local container=$1
    docker stats "$container" --no-stream --format "{{.CPUPerc}}" | sed 's/%//'
}

manage_container() {
    local container=$1
    local action=$2
    local core=${CORE_ASSIGNMENTS[$container]}
    
    case $action in
        "start")
            log_message "Starting $container on CPU $core"
            docker run -d --name "$container" --cpuset-cpus="$core" --restart unless-stopped "$IMAGE"
            sleep 10
            ;;
        "stop")
            log_message "Stopping $container"
            docker stop "$container" >/dev/null
            docker rm "$container" >/dev/null
            ;;
    esac
}

update_containers() {
    log_message "Pulling the latest image..."
    if docker pull "$IMAGE" | grep -q 'Downloaded newer image'; then
        log_message "New image version detected. Updating containers..."
        for container in "${CONTAINERS[@]}"; do
            if [[ $(check_container_status "$container") == "running" ]]; then
                manage_container "$container" "stop"
                manage_container "$container" "start"
            fi
        done
    fi
}

check_and_scale() {
    for container in "${CONTAINERS[@]}"; do
        local status=$(check_container_status "$container")
        
        if [[ $container == "service1" && $status != "running" ]]; then
            manage_container "$container" "start"
        elif [[ $status == "running" ]]; then
            local usage1=$(get_cpu_usage "$container")
            sleep 20
            local usage2=$(get_cpu_usage "$container")
            
            if (( $(echo "$usage1 > 80" | bc -l) && $(echo "$usage2 > 80" | bc -l) )); then
                local next_container=${CONTAINERS[$(( ${!CONTAINERS[@]} + 1 ))]}
                if [[ $(check_container_status "$next_container") != "running" ]]; then
                    log_message "$container is overloaded. Starting $next_container"
                    manage_container "$next_container" "start"
                fi
            elif (( $(echo "$usage1 < 10" | bc -l) && $(echo "$usage2 < 10" | bc -l) )); then
                log_message "$container is idle. Stopping it..."
                manage_container "$container" "stop"
            fi
        fi
    done
}

main() {
    local last_update=0
    
    log_message "Starting container management service"
    while true; do
        check_and_scale
        
        local current_time=$(date +%s)
        if (( current_time - last_update >= 600 )); then
            update_containers
            last_update=$current_time
        fi
        
        sleep 20
    done
}

main
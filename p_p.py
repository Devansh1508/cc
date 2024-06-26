class Process:
    def __init__(self, pid, priority ,arrival_time, burst_time):
        self.pid = pid
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.priority = priority
        self.remaining_time = burst_time
        self.start_time = 0
        self.completion_time = 0
        self.waiting_time = 0
        self.turnaround_time = 0
        self.response_time = -1  

def priority_preemptive(processes):
    total_processes = len(processes)
    current_time = 0
    completioned_processes = 0
    gantt_chart = []

    while completioned_processes < total_processes:
        min_priority = float('inf')
        selected_process = None

        for process in processes:
            if process.arrival_time <= current_time and process.remaining_time > 0:
                if process.priority < min_priority:
                    min_priority = process.priority
                    selected_process = process

        if selected_process is None:
            current_time += 1
            gantt_chart.append("Idle")
        else:
            if selected_process.response_time == -1:
                selected_process.response_time = current_time - selected_process.arrival_time
            if selected_process.remaining_time == selected_process.burst_time:
                selected_process.start_time = current_time
            selected_process.remaining_time -= 1
            current_time += 1
            gantt_chart.append(selected_process.pid)

            if selected_process.remaining_time == 0:
                selected_process.completion_time = current_time
                selected_process.turnaround_time = selected_process.completion_time - selected_process.arrival_time
                selected_process.waiting_time = selected_process.turnaround_time - selected_process.burst_time
                completioned_processes += 1

    return gantt_chart

def display_table(processes):
    total_waiting_time = 0
    total_response_time = 0
    total_turnaround_time = 0
    
    print("Priority\tPID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\tResponse Time")
    for process in processes:
        total_response_time += process.response_time
        total_waiting_time += process.waiting_time
        total_turnaround_time += process.turnaround_time
        
        print(f"{process.priority}\t\t{process.pid}\t{process.arrival_time}\t\t{process.burst_time}\t\t{process.completion_time}\t\t"
              f"{process.turnaround_time}\t\t{process.waiting_time}\t\t{process.response_time}")
    
    avg_waiting_time = total_waiting_time / len(processes)
    avg_response_time = total_response_time / len(processes)
    avg_turnaround_time = total_turnaround_time / len(processes)
    
    print("\nAverage Waiting Time:", avg_waiting_time)
    print("Average Response Time:", avg_response_time)
    print("Average Turnaround Time:", avg_turnaround_time)

if __name__ == "__main__":
    processes = [
        Process("P1", 3, 1, 8),
        Process("P2", 2, 3, 4),
        Process("P3", 1, 3, 2),
        Process("P4", 2, 5, 4),
        Process("P5", 1, 7, 2),
        Process("P6", 1, 8, 2),
        # Process("P7", 1, 10, 1),       
    ]

    gantt_chart = priority_preemptive(processes)
    print("Gantt Chart:")
    print(gantt_chart)
    print("\n")

    display_table(processes)

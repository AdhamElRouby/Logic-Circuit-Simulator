import matplotlib.pyplot as plt  # type: ignore

def read_sim_file(filename):
    """Reads the .sim file and returns a dictionary of signals with their corresponding time and value lists."""
    signals = {}
    
    with open(filename, 'r') as file:
        for line in file:
            time, signal, value = line.strip().split(', ')
            time = int(time)  # Time is already in ns
            value = int(value)
            
            if signal not in signals:
                signals[signal] = {'time': [], 'value': []}
                
            signals[signal]['time'].append(time)
            signals[signal]['value'].append(value)
    
    return signals

def plot_waveforms(signals):
    """Plots the waveforms of the signals, with undefined areas indicated in dotted red lines."""
    plt.figure(figsize=(12, len(signals) * 1.5))
    plt.title("Digital Signal Waveforms (Time in ns)")
    
    max_time = max(max(data['time']) for data in signals.values())  # Find the max time
    
    colors = plt.cm.tab10.colors  # Using a color map for distinct colors
    for i, (signal, data) in enumerate(signals.items()):
        times = data['time']
        values = data['value']
        
        # Offset for this signal on the y-axis
        offset = i * 2
        
        # Assign a distinct color for each signal
        color = colors[i % len(colors)]
        
        # Draw the undefined area as dotted red until the first mention
        first_time = times[0]  # Time when signal is first mentioned
        if first_time > 0:
            plt.plot([0, first_time], [offset + 1, offset + 1], color='red', linewidth=1.5, linestyle=':')
            plt.text(first_time / 2, offset + 1.1, "Undefined", color='red', ha='center', va='bottom', fontsize=8)
        
        # Plot the actual signal waveform starting from the first mention
        extended_times = times + [max_time]
        extended_values = values + [values[-1]]  # Extend the last value to max_time
        
        # Plot the defined waveform with assigned color
        plt.step(extended_times, [val + offset for val in extended_values], where='post', color=color, linewidth=2)
        
        # Adding signal name to the left of the plot with increased font size
        plt.text(-60, offset + 1, signal, fontsize=12, ha='right', va='center')
    
    # Adding grid lines to clarify the time scale
    plt.xticks(range(0, max_time + 100, 100))  # Major ticks every 100 ns
    plt.grid(axis='x', linestyle='--', alpha=0.7)

    # Adjusting y-ticks
    plt.yticks([i * 2 for i in range(len(signals))], [''] * len(signals))  # No variable names
    plt.xlabel("Time (ns)")
    plt.tight_layout()
    plt.show()

# Main function to read the file and plot
filename = 'D:\\python bonus\\output.sim'  # Specify your file path here
signals = read_sim_file(filename)
plot_waveforms(signals)

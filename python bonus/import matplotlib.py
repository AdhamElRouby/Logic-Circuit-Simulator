import matplotlib.pyplot as plt

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
    """Plots the waveforms of the signals."""
    plt.figure(figsize=(12, len(signals) * 1.5))
    plt.title("Digital Signal Waveforms (Time in ns)")
    
    max_time = max(max(data['time']) for data in signals.values())  # Find the max time
    
    for i, (signal, data) in enumerate(signals.items()):
        times = data['time']
        values = data['value']
        
        # Create a new time and value list that includes only mentioned times
        extended_times = []
        extended_values = []

        # Track the current level (default is to start drawing only when mentioned)
        last_time = 0  # Initialize the last time point
        current_level = None  # Start with no defined level

        # Iterate through the time and value pairs
        for j in range(len(times)):
            # If there's a gap in time, we need to draw the current level until the next time point
            while last_time < times[j]:
                extended_times.append(last_time)
                if current_level is not None:
                    extended_values.append(current_level)  # Only append if the level is defined
                else:
                    extended_values.append(None)  # No defined level yet
                last_time += 1  # Increment time by 1 ns

            # Now, add the time and value for the signal
            extended_times.append(times[j])
            extended_values.append(values[j])
            current_level = values[j]  # Update the current level

            last_time = times[j] + 1  # Move to the next time after the current one
        
        # Extend the last value to the maximum time
        extended_times.append(max_time)
        if current_level is not None:
            extended_values.append(current_level)
        else:
            extended_values.append(None)  # No defined level until first mention

        # Offset the waveform vertically for each signal to avoid overlap
        offset = i * 2  # Increase spacing by multiplying by 2
        
        # Filter out None values for plotting
        filtered_times = []
        filtered_values = []
        for t, v in zip(extended_times, extended_values):
            if v is not None:  # Only include defined levels
                filtered_times.append(t)
                filtered_values.append(v + offset)

        plt.step(filtered_times, filtered_values, where='post')

        # Adding signal name to the left of the plot with increased font size
        plt.text(-60, offset + 1, signal, fontsize=12, ha='right', va='center')  # Shifted left
    
    # Adding grid lines to clarify the time scale
    plt.xticks(range(0, max_time + 100, 100))  # Major ticks every 100 ns
    plt.grid(axis='x', linestyle='--', alpha=0.7)

    # Adding y-ticks for clarity
    plt.yticks([i * 2 for i in range(len(signals))], [''] * len(signals))  # No variable names
    plt.xlabel("Time (ns)")
    plt.tight_layout()
    plt.show()

# Main function to read the file and plot
filename = 'D:\\python bonus\\output.sim'  # Specify your file path here
signals = read_sim_file(filename)
plot_waveforms(signals)

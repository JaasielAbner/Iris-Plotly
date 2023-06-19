import plotly.graph_objects as go
import numpy as np

def read_data(filename):
    class1 = []
    class2 = []
    class3 = []

    with open(filename, 'r') as file:
        count = 0
        for line in file:
            print(line)
            if line.split()[0]=="Class":
                count+=1
            else:
                data = line.split(',')
                # Converting the other values to floats
                features = list(map(float, data))
                if count == 1:
                    class1.append(features)
                elif count == 2:
                    class2.append(features)
                elif count == 3:
                    class3.append(features)
    
    return class1, class2, class3

# Example usage:
filename = 'aa.out'  # Replace with your file path
class1, class2, class3 = read_data(filename)

# Create a scatter plot for each class
fig = go.Figure()

# Class 1
fig.add_trace(go.Scatter3d(
    x=[point[0] for point in class1],
    y=[point[1] for point in class1],
    z=[point[2] for point in class1],
    mode='markers',
    marker=dict(
        size=[point[3] * 20 for point in class1],  # Scale the marker size for the fourth dimension
        color='blue',
        opacity=0.7
    ),
    name='Class 1'
))

# Class 2
fig.add_trace(go.Scatter3d(
    x=[point[0] for point in class2],
    y=[point[1] for point in class2],
    z=[point[2] for point in class2],
    mode='markers',
    marker=dict(
        size=[point[3] * 20 for point in class2],  # Scale the marker size for the fourth dimension
        color='red',
        opacity=0.7
    ),
    name='Class 2'
))

# Class 3
fig.add_trace(go.Scatter3d(
    x=[point[0] for point in class3],
    y=[point[1] for point in class3],
    z=[point[2] for point in class3],
    mode='markers',
    marker=dict(
        size=[point[3] * 20 for point in class3],  # Scale the marker size for the fourth dimension
        color='green',
        opacity=0.7
    ),
    name='Class 3'
))

# Set the layout of the plot
fig.update_layout(
    scene=dict(
        xaxis_title='Feature 1',
        yaxis_title='Feature 2',
        zaxis_title='Feature 3'
    ),
    title='4D Scatter Plot',
    showlegend=True
)

# Display the plot
fig.show()

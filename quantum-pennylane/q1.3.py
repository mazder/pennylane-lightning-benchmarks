"""
If we measure a qubit in this state, we'll observe  64% of the time (), and  36% of the time. Therefore, an example set of 10 measurement outcomes might be

[0, 1, 1, 1, 0, 1, 0, 0 ,0 ,0]
"""


import pennylane as qml
from pennylane import numpy as np

def measure_state(state, num_meas):
    """Simulate a quantum measurement process.

    Args:
        state (array[complex]): A normalized qubit state vector. 
        num_meas (int): The number of measurements to take
        
    Returns:
        array[int]: A set of num_meas samples, 0 or 1, chosen according to the probability 
        distribution defined by the input state.
    """

    ##################
    # YOUR CODE HERE #
    ##################
    
    # COMPUTE THE MEASUREMENT OUTCOME PROBABILITIES

    # RETURN A LIST OF SAMPLE MEASUREMENT OUTCOMES
    aa=state[0]*np.conj(state[0])
    bb=state[1]*np.conj(state[1])
    return np.random.choice(np.array([0,1]), num_meas, p=np.array([aa.real,bb.real]))
    pass

state = np.array([0.8, 0.6])

print(measure_state(state,10))

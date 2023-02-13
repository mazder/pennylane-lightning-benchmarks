import pennylane as qml
from pennylane import numpy as np

Uh = np.array([[1, 1], [1, -1]]) / np.sqrt(2)

def apply_u(U,state):
    """Apply a quantum operation.

    Args:
        state (array[complex]): A normalized quantum state vector. 
        
    Returns:
        array[complex]: The output state after applying U.
    """

    ##################
    # YOUR CODE HERE #
    ##################

    # APPLY U TO THE INPUT STATE AND RETURN THE NEW STATE
    return U.dot(state)
    pass

Un = np.array([[0, 1], [1, 0]])
state = np.array([0.8, 0.6])

print(apply_u(Un,state))
print(apply_u(Uh,state))



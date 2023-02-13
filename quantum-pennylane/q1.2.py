import pennylane as qml
from pennylane import numpy as np


def normalize_state(alpha, beta):
     """Compute a normalized quantum state given arbitrary amplitudes.
     
     Args:
         alpha (complex): The amplitude associated with the |0> state.
         beta (complex): The amplitude associated with the |1> state.
         
     Returns:
         array[complex]: A vector (numpy array) with 2 elements that represents
         a normalized quantum state.
     """
     # CREATE A VECTOR [a', b'] BASED ON alpha AND beta SUCH THAT |a'|^2 + |b'|^2 = 1
     # RETURN A VECTOR
     return np.array([alpha/(np.conj(alpha)*alpha+np.conj(beta)*beta)**(1/2),beta/(np.conj(alpha)*alpha+np.conj(beta)*beta)**(1/2)])
     pass

alpha = 2.0 + 1.0j
beta = -0.3 + 0.4j
ket_alpha_beta = normalize_state(alpha,beta)
print(ket_alpha_beta)
 

def inner_product(state_1, state_2):
    """Compute the inner product between two states.
    
    Args:
        state_1 (array[complex]): A normalized quantum state vector
        state_2 (array[complex]): A second normalized quantum state vector
        
    Returns:
        complex: The value of the inner product <state_1 | state_2>.
    """
 
    ##################
    # YOUR CODE HERE #
    ##################

    # COMPUTE AND RETURN THE INNER PRODUCT
    return np.conj(state_2[0]*state_1[0]+np.conj(state_2[1])*state_1[1])
    pass 


# Test your results with this code
ket_0 = np.array([1, 0])
ket_1 = np.array([0, 1])

print(f"<0|0> = {inner_product(ket_0, ket_0)}")
print(f"<0|1> = {inner_product(ket_0, ket_1)}")
print(f"<1|0> = {inner_product(ket_1, ket_0)}")
print(f"<1|1> = {inner_product(ket_1, ket_1)}")

print(f"<a|a> = {inner_product(ket_alpha_beta, ket_alpha_beta)}")


state_1 = np.array([0.8, 0.6])
state_2 = np.array([1 / np.sqrt(2), 1j / np.sqrt(2)]) 

print(f"<state_1|state_1> = {inner_product(state_1, state_1)}")
print(f"<state_1|state_2> = {inner_product(state_1, state_2)}")
print(f"<state_2|state_1> = {inner_product(state_2, state_1)}")
print(f"<state_2|state_2> = {inner_product(state_2, state_2)}")




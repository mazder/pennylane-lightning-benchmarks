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
print(normalize_state(alpha,beta))

"""
output
[ 0.87287156+0.43643578j -0.13093073+0.17457431j]
|w>=(0.87287156+0.43643578i)|0> + (-0.13093073+0.17457431i)|1>
""" 

import math

# Function to calculate the distance between two vectors
def distnce(v1, v2):
    sum = 0
    for i in range(len(v1)):
        sum += (v1[i] - v2[i]) ** 2
    sum = math.sqrt(sum)
    return sum

# Function to find the closest centroid to a vector
def find_closest_centroid(v, centroids, k):
    min = float('inf')
    min_index = -1
    for i in range(k):
        curr_d = distnce(v, centroids[i])
        if (curr_d < min):
            min = curr_d
            min_index = i
    return min_index

# Function to compute the new centroid of a cluster
def compute_new_centroid(cluster, vec_len):
    sum = [0 for i in range(vec_len)]
    for vector in cluster:
        for i in range(vec_len):
            sum[i] += vector[i]
    for i in range(vec_len):
        sum[i] /= len(cluster)
    return sum

# Function to update the centroids of the clusters and check if the delta is legal
def update_centroids_and_legal_delta(clusters, centroids, k, vec_len):
    delta = [False for i in range(k)]
    for i in range(k):
        new_cent = compute_new_centroid(clusters[i], vec_len)
        if distnce(new_cent, centroids[i]) < 0.001:
            delta[i] = True
    if False in delta:
        return False
    return True
            

def k_means_cluster(k, iter, filename):
    
    # Read the data from the file and add all the vectors to a list
    vectors = []
    my_file = open(filename, "r")
    for line in my_file:
        vectors.append([float(x) for x in line.split(',')])

    # assert correct values of k and iter
    if not (1 < k < len(vectors)):
        print("Invalid number of clusters!")
        return
    if not (1 <= iter < 1000):
        print("Invalid maximum iteration!")
        return
    
    # initialize vector len vec_len
    vec_len = len(vectors[0])
    
    # Initialize the centroids and the clusters
    centroids = vectors[:k]
    clusters = [[] for i in range(k)]

    for i in range(iter):

        # init different clusters array
        clusters = [[] for i in range(k)]

        for vector in vectors:
            j = find_closest_centroid(vector, centroids, k)
            clusters[j].append(vector)

        # update the centroids
        is_done = update_centroids_and_legal_delta(clusters, centroids, k, vec_len)

        if is_done:
            break
    print(centroids)
    return centroids
            

k_means_cluster(3,1,"hw1.txt")

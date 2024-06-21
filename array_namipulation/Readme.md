# Array Manipulation

## Indexing and Slicing

### One-dimensional Indexing and Slicing

1. **Basic Indexing**
Single element indexing works exactly like that for other standard Python sequences. It is 0-based, and accepts negative indices for indexing from the end of the array.

   1. **Single Element Indexing**
        As in Python, all indices are zero-based: for the i-th index $`n_i`$ the valid range is $`0\leq n_{i}\lt d_{i}`$ where $`d_{i}`$ is the i-th element of the shape of the array. Negative indices are interpreted as counting from the end of the array (i.e, if $`{n}_{i}\lt 0`$, it means $`n_{i}+d_{i}`$)

        ```python
        # Indexing the element of 1D array
        x = np.arange(10)
        print(x)
        print(x[2]) # Indexing from the 11st element
        print(x[-2]) # Indexing from the last element
        ```

        ```output
        <<Output
        [0 1 2 3 4 5 6 7 8 9]

        2
        8
        ```

        ```python
        # Boolean indexing
        bool_mask = x > 5

        print(x[bool_mask])
        ```

        ```output
        <<Output
        [6 7 8 9]
        ```

        ```python
        # Fancy indexing
        indices = np.array([0, 2, 4])
        print(x[indices])
        ```

        ```output
        <<Output
        [0 2 4]
        ```

   2. **Slicing and striding**
        - The basic slice syntax is `i:j:k` where,
  
            - **i is the starting index,**
            - **j is the stopping index,**
            - **k is the step** where ($`k\neq0`$).

        ```python
        x = np.array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
        x[1:7:2]
        ```

        ```output
        <<Output
        array([1, 3, 5])
        ```

        - Negative i and j are interpreted as n + i and n + j where n is the number of elements in the corresponding dimension. Negative k makes stepping go towards smaller indices.
  
        ```python
        print(x[-3:10])
        print(x[-3:2:-1])
        ```

        ```output
        <<Output
        [7 8 9]

        [7 6 5 4 3]
        ```

       - Assume n is the number of elements in the dimension being sliced. Then, if i is not given it defaults to 0 for k > 0 and n - 1 for k < 0 . If j is not given it defaults to n for k > 0 and -n-1 for k < 0 . If k is not given it defaults to 1. Note that `::` is the same as `:` and means select all indices along this axis.

        ```python
        print(x[5:])
        print(x[5::])

        print(x[:5])
        print(x[::5])
        ```

        ```output
        <<Output
        [5 6 7 8 9]
        [5 6 7 8 9]

        [0 1 2 3 4]
        [0 5]
        ```

        1. `x[5:] == x[5::]`
            In this case, x[5:] and x[5::] are equivalent because, by default, when the step parameter is not provided, it is assumed to be 1. So, both slices mean "start from index 5 and go to the end of the array with a step of 1."

        2. `x[:5] !== x[::5]`

            Here, x[:5] and x[::5] are not equivalent. x[:5] means "start from the beginning and go up to index 5 (exclusive) with a step of 1," whereas x[::5] means "start from the beginning and go up to the end with a step of 5."

### Multi-dimensional Indexing and Slicing

1. **Indexing**

    ```python
    # Indexing the element of 2D array/matrix
    x.shape = (2, 5) 
    print(x)
    print(x[1, 2])
    ```

    ```output
    <<Output
    [[0 1 2 3 4]
    [5 6 7 8 9]]

    7
    ```

   - Indexing a multidimensional array with fewer indices than dimensions, we get a subdimensional array

    ```python
    x[0]
    ```

    ```output
    <<Output
    array([0, 1, 2, 3, 4])
    ```

    - Here `x[0][2] == x[0, 2]` since, second case is more inefficient as a new temporary array is created after first index which is subsequently indexed by 2 

    ```python
    print(x[0][1])
    print(x[0,1])
    ```

    ```output
    <<Output
    1
    1
    ```

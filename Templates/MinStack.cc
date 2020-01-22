class MinStack {
public:
    int _size = 0;
    // a存放指向b的下标，b存放数据，ia(inverse_a)由b中下标指向a
    int a[100001], b[100001], ia[100001];

    /** initialize your data structure here. */
    MinStack() {
    }
    
    void swap(int x, int y) {
        int tmp = a[x];
        a[x] = a[y];
        a[y] = tmp;
        
        ia[a[x]] = x;
        ia[a[y]] = y;
    }
    
    void heapify(int i) {
        int smallest = i;
        int l = i * 2, r = i * 2 + 1;
        if (l <= _size && b[a[l]] < b[a[smallest]]) smallest = l;
        if (r <= _size && b[a[r]] < b[a[smallest]]) smallest = r;
        if (smallest != i) {
            swap(i, smallest);
            heapify(smallest);
        }
    }
    
    void decrease_key(int i) {
        int parent = i / 2;
        if (parent == 0) return;
        if (b[a[i]] < b[a[parent]]) {
            swap(i, parent);
            decrease_key(parent);
        }
    }
    
    void push(int x) {
        _size++;
        b[_size] = x;
        a[_size] = _size;
        ia[_size] = _size;
        decrease_key(_size);
    }
    
    void pop() {
        assert(_size);
        _size--;
        int index = ia[_size+1];
        swap(index, _size+1);
        heapify(index);
    }
    
    int top() {
        assert(_size);
        return b[_size];
    }
    
    int getMin() {
        assert(_size);
        return b[a[1]];
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
import random
from ctypes import cdll, c_bool, c_float, c_int, pointer, POINTER, Structure


class CTreeNode(Structure):
    pass


CTreeNode._fields_ = [("key", c_int),
                      ("value", c_float),
                      ("left", POINTER(CTreeNode)),
                      ("right", POINTER(CTreeNode))]


class CTree:

    code = None

    def __init__(self):
        if CTree.code is None:
            CTree.code = cdll.LoadLibrary("libtree.so")
            CTree.code.insert.argtypes = [POINTER(CTreeNode), c_int, c_float]
            CTree.code.insert.restype = POINTER(CTreeNode)
            CTree.code.search.argtypes = [POINTER(CTreeNode),
                                          c_int, POINTER(c_float)]
            CTree.code.search.restype = c_bool
            CTree.code.destroy.argtypes = [POINTER(CTreeNode)]
        self.root = POINTER(CTreeNode)()

    def search(self, key):
        return CTree.code.search(self.root, key)

    def insert(self, key, value):
        return CTree.code.insert(self.root, key, value)

    def __str__(self):
        pass

    def __del__(self):
        CTree.code.destroy(self.root)


class Node:

    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.leftSon = None
        self.rightSon = None

    def search(self, key):
        if self.key == key:
            return self.value
        elif self.key < key:
            if self.rightSon is None:
                return None
            return self.rightSon.search(key)
        else:
            if self.leftSon is None:
                return None
            return self.leftSon.search(key)
        

    def insert(self, key, value):
        if self.key == key:
            self.value = value
        elif self.key < key:
            if self.rightSon is None:
                self.rightSon = Node(key,value)
            else:
                self.rightSon.insert(key,value)
        else:
            if self.leftSon is None:
                self.leftSon = Node(key,value)
            else:
                self.leftSon.insert(key,value)

    def __str__(self):
        return f"({self.key} {str(self.leftSon)} {str(self.rightSon)})"


class BinarySearchTree:

    def __init__(self):
        self.radice = None

    def search(self, key):
        if self.radice is not None:
            return self.radice.search(key)
        return None

    def insert(self, key, value):
        if self.radice is not None:
            self.radice.insert(key,value)
        else:
            self.radice = Node(key,value)

    def __str__(self):
        return f"{str(self.radice)}"


if __name__ == "__main__":
    # bst = BinarySearchTree()
    # for i in range(0, 20):
    #     bst.insert(random.randint(0, 30), random.random())
    # for i in range(0, 10):
    #     k = random.randint(0, 30)
    #     print(f"Searching for {k}: {bst.search(k)}")
    # print(bst)

    # Decommentare per la parte extra
    cbst = CTree()
    for i in range(0, 20):
        cbst.insert(random.randint(0, 30), random.random())
    for i in range(0, 10):
        k = random.randint(0, 30)
        print(f"Searching for {k}: {cbst.search(k)}")
    print(cbst)

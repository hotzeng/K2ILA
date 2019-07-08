class BTree(object):
    "can have one or multiple children"
    def __init__(self, name='root', children=None):
        self.name = name
        self.children = []
        if children is not None:
            for child in children:
                self.add_child(child)

    def __repr__(self):
        return self.name

    def add_child(self, child):
        assert isinstance(child, BTree)
        self.children.append(child)

    def set_name(self, name):
        self.name = name

    def set_children_no(self, no):
        assert len(self.children) == 0
        for i in range(no):
            self.children.append(None)

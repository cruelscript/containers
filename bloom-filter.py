from bitarray import bitarray
import mmh3


class BloomFilter(set):
    def __init__(self, size, hash_count):
        super(BloomFilter, self).__init__()
        self.bits = bitarray(size)
        self.bits.setall(0)
        self.size = size
        self.hash_count = hash_count

    def __len__(self):
        return self.size

    def __iter__(self):
        return iter(self.bits)

    def add(self, item):
        for i in range(self.hash_count):
            index = mmh3.hash(item, i) % self.size
            self.bits[index] = 1
        return self

    def __contains__(self, item):
        contains = True
        for i in range(self.hash_count):
            index = mmh3.hash(item, i) % self.size
            if self.bits[index] == 0:
                contains = False
        return contains


bf = BloomFilter(100, 10)
animals = ['dog', 'cat', 'giraffe', 'fly', 'mosquito', 'horse', 'eagle',
           'bird', 'bison', 'boar', 'butterfly', 'ant', 'anaconda', 'bear',
           'chicken', 'dolphin', 'donkey', 'crow', 'crocodile']
other_animals = ['badger', 'cow', 'pig', 'sheep', 'bee', 'wolf', 'fox',
                 'whale', 'shark', 'fish', 'turkey', 'duck', 'dove',
                 'deer', 'elephant', 'frog', 'falcon', 'goat', 'gorilla',
                 'hawk']

for animal in animals:
    bf.add(animal)

for animal in animals + other_animals:
    if animal in animals:
        if animal in bf:
            print('{} is in bloom filter as expected'.format(animal))
        else:
            print('This should never be printed')

    elif animal in other_animals:
        if animal in bf:
            print('{} is false positive in bloom filter'.format(animal))
        else:
            print('{} is not in bloom filter as expected'.format(animal))

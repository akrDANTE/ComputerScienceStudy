### All About python language

#### 1. Chapter 1 - pythonic thinking.

1. PEP 8 style guide: https://www.python.org/dev/peps/pep-0008/
2. Bytes vs str:\
   bytes == raw unsigned 8-bit values(displayed in ASCII encoding)\
    a = b'h\x65llo' (b'hello'), print(list(a)) = [104, 101, 108, 108, 111]\
   str == unicode code points that represent text characters\
    a = 'a\u0300 propos'\
   to convert unicode data to binary data must call encode method.\
   isinstance(bytes_or_str, str)\
   assert 'red' > 'blue'\
   string formatting : 'red %s' % 'blue' == 'red blue'\
   string formatting: f'red {"blue"}' \
   strign formatting: '#%(loop)d: %(item)-10s = %(count)d' % {'loop': i, 'item': title, 'count': round(count)}\
   string formatting: a = 1234.5678; formatted = format(a, ',.2f')\
   string formatting: b = 'my string'; formatted = format(b, '^20s')\
   string formatting: '{} = {}'.format(key, value)\
   see help('FORMATTING') for all possible options\
   escape {} using {{}} doubling.\
   string formatting: '{1} = {0}'.format(key, value)
   enumerate(dict) => serial number, key
3. Yield keyword in python, when used in a function returns a generator object. And at the point of yield statement execution is stopped. After we call next or iterate over the generator object then only next statements are executed. Useful for saving memory and dealing with large dataset.
4. use zip for iterating multiple lists(of same length) at same time.\
   use itertools.zip_longest for lists of different lengths.
5. Finally keyword is used for always doing something after a try block has failed.
6. assert keyword throws exception if condition is not satisfied.
7. := walrus operator is assignment operator that returns the value of the lhs after assigning the value. For example: if count := get_count():

#### Chapter 2 : Lists and dictionaries.

1.

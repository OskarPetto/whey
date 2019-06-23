# WheyVM
## Typesystem
A stack based VM that support the following operands
  * Integer
  * Double 
  * Reference 
where a reference points to an Object, which can be 
  * Integer 
  * Double 
  * String 
  * Array 
  * Map 
  * Pair 
The memory claimed by objects are freed with a simple mark and sweep garbage collector. 
## Fileformat
The instructions are provided in a file format calles WcFile. 

# WheyVM
## Typesystem
A stack based VM that support the following operands
  * Integer
  * Double 
  * Reference
[//]: # (Hello)
where a reference points to an Object, which can be 
  * Integer 
  * Double 
  * String 
  * Array 
  * Map 
  * Pair 
[//]: # (Hello)
The memory claimed by objects are freed with a simple mark and sweep garbage collector. 
## Fileformat
The instructions are provided in a file format calles WcFile. 

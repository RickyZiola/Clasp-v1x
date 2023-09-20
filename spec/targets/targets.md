# Clasp build targets
Build targets are a directory containing standard libraries, assembler binaries, and parse visitors.  
These can also be compressed using zipfile compression
## File structure
- `lib/` directory contains standard libraries. These handle complex maths, kernel calls, and anything else included in the standard libraries.  
    - The entire standard library doesn't need to be implemented, but any programs that use unimplemented stdlib modules won't compile with the selected build target.  
- `bin/` directory contains assembler binaries. This could be `nasm`, `customasm`, or some custom assembler.  
    - This is used as a utility and accessed from the target configurations  
- `conf/` directory contains target configuration such as preprocessors, post-processors, and parse tree visitors. These are further defined below.  
## Configuration syntax / structure
TODO
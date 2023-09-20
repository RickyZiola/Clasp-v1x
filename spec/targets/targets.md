# Clasp build targets
Build targets are a directory containing standard libraries, assembler binaries, and parse visitors.  
These can also be compressed using zipfile compression
## File structure
- `lib/` directory contains standard libraries. These handle complex maths, kernel calls, and anything else included in the standard libraries.  
    - The entire standard library doesn't need to be implemented, but any programs that use unimplemented stdlib modules won't compile with the selected build target.  
- `bin/` directory contains assembler binaries. This could be `nasm`, `customasm`,s or some custom assembler.  
    - This is used as a utility and accessed from the target configurations  
- `conf/` directory contains target configuration such as preprocessors, post-processors, and parse tree visitors. These are further defined below.  
## Configuration syntax / structure
- \<target_name>.json: contains filepaths to preprocessers, postprocessers and visitors.  
- \<anything>.vst: contains a visitor. This is further defined below.  
## JSON configs
- These must contain a few properties:  
    - `preprocesser_path`: a string, the path to the preprocesser (relative to the base of the target directory) or `""` for no preprocesser. The preprocesser should take 2 arguments, `input` and `output` (both paths to the input / output files), in that order.  

    - `postprocesser_path`: a string, the path to the postprocesser/assembler (relative to the base of the target directory) or `""` for no postprocesser. The postprocesser should take 2 arguments, `input` and `output` (both paths to the input / output files), in that order.  

    - `visitor_path`: a string, the path to the parse tree visitor (relative to the `conf/` directory). This must not be `""`.

## Visitors
- These are a custom (but simple) file format that contain visitor data, TODO.
# external_sort
## Generate large file
Use
```bash
python generator.py -o test -l 300 --max 10 --min 1
```
to generate file with name `test` with 300 lines of size from 1 to 10 MB.

## Sort large files
Use
```bash
./external_sort -I test -M 100 -O data
```
to sort file `test` with max RAM of 100MB to output file `data`
### Merge explanation
We use tree-like merge to be memory size independent of file size. We can do it easier with iterating through all of the chunks at the same time, however this will require additional memory usage.

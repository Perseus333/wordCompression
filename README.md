# WordCompression

***A small program that compresses a dictionary of words into smaller, somewhat legible, words.***

## Configuration

If you want to you can configure it so that it compresses any dictionary that you want

If you want to change the dictionary and it has a different size than the default, 10k, just replace the file in `data/` for your own dictionary. For better results the words should be ordered by frequency. The format must be like so with a newline at the end:

```
word1
word2
word3
...

```

Afterwards, change the definition `MAX_CHARS_PER_WORD` in `include/word_utils.h` to the longest word in your dictionary. Also change `TOTAL_WORDS` so that it is equal to the amount of words in your dictionary.

If you want to change some other variables all of them will be at `include/word_utils.h`.

## How to install

1. Download the file corresponding to your OS from the releases. 
2. Run `main.exe` from the `/bin` folder. 

## How to build

1. From the command-line run:

```bash
git clone https://github.com/Perseus333/wordCompression.git
cd wordCompression
```

2. To compile the program:

```bash
make
```

3. And to run it:
```bash
./bin/main.exe
```

To edit variables, edit the definitions in `include/word_utils.h`.

## Stats

### Speed

Initial version (feat: measure elapsed time): 660 ms

Latest optimized version (optmz: linked lists): 78 ms

### Compression ratio

With the default 10k dictionary at the latest release the compression ratio is **66.21%**.

## License
Released under the MIT License. See `LICENSE` for more information.
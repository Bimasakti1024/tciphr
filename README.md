# tciphr

`tciphr` is a lightweight command-line interface to process text using historical cryptographic algorithms. It allows people like CTF player to process text through classic ciphers right from the terminal.

## Security Notice

This tool implements historical cryptographic algorithms which does not adhere to modern security standards.

## Installation

### Requirements

- C99 Compatible compiler
- CMake 3.10+
- Standard C Library

### Build

```bash
cmake -B build
cmake --build build
```

## Usage

```bash
tciphr -c <cipher> [-k <key>] [-d] [-C] [-v] [-l] [-p] [-h]
```

| Flag        | Description        |
| -------------| --------------------|
| -c <cipher> | Cipher to use      |
| -k <key>    | Cipherkey          |
| -d          | Decode             |
| -C          | Crack              |
| -p          | Cracking parameter |
| -v          | Verbose            |
| -l          | List ciphers       |
| -h          | Show help          |

`tciphr` operates as pipeline filter, It read text from `stdin` and output them to `stdout`.

A cracking parameter are used to input data to the cracking engine, Like for dictionary attack it would require the wordlist path to be passed using cracking parameter.

### Example

```bash
$ echo "the quick brown fox jumps over a lazy dog" | tciphr -c vigenere -k secret
llg hybuo dispf jqo nnetu fzxj e nrdr vsi
$
```

This example shows a usage of tciphr to encode the text "the quick brown fox jumps over a lazy dog" using vigenere cipher with the key "secret".

You can also use another cipher, like railfence cipher:

```bash
$ echo "the quick brown fox jumps over a lazy dog" | tciphr -c railfence -k 3
tqkofjse ygh uc rw o up vralz oeibnxmo ad
$
```

You can also decode a cipher, Railfence cipher for example:

```bash
$ echo "tqkofjse ygh uc rw o up vralz oeibnxmo ad" | tciphr -c railfence -k 3 -d
the quick brown fox jumps over a lazy dog
$
```

This example shows how to work with files:

```bash
$ cat message.txt | tciphr -c rot13 > encoded.txt
$
```

Vigenere cipher and some others can be broken by dictionary attack like this:

```bash
$ echo "bsog{fkewvr_pqyawozinf_otfiyr}" | ./tciphr -Cc vigenere -p strategy=dictionary,wordlist=wordlist.txt
Cipherkey hello: uodv{rdalkd_imnpihvxcr_hpuxkk}
Cipherkey fox: werb{rnziym_bttmzjllir_rorltd}
Cipherkey password: mswo{jwntgr_xycmflkivn_sfofjr}
Cipherkey whoami: flag{tciphr_dictionary_attack}
Cipherkey onetwothree: nfkn{jwlpen_lclwdslpgo_kprvuy}
$
```

The ciphertext "bsog{fkewvr_pqyawozinf_otfiyr}" is decoded using every cipherkey in `wordlist.txt`, The correct plaintext also has a recognizable pattern ("flag") which the output can be piped to other tools like `grep`.

Vigenere cipher supports two strategies of cracking it: Dictionary and Kasiski (frequency analysis). This is an example of how to use kasiski strategy to crack vigenere cipher:

```bash
$  cat cap_excerpt.txt | tciphr -c vigenere -k hello | tciphr -Cc vigenere -p strategy=kasiski,gram=3
Predicted key length: 5
Index of coincidence: 0.035894
Best letter frequency: 11 (l)
Possible column 0 key: h
Best letter frequency: 8 (i)
Possible column 1 key: e
Best letter frequency: 15 (p)
Possible column 2 key: l
Best letter frequency: 15 (p)
Possible column 3 key: l
Best letter frequency: 18 (s)
Possible column 4 key: o
Possible key: hello
$ 
```

This example works by first piping the file `cap_excerpt.txt` to tciphr for encoding using vigenere cipher, then piping the output back into tciphr to crack it using kasiski strategy (frequency analysis), which successfully recovers the key.

### Supported ciphers

| Cipher    | Category                    | Key requirement     | Cracking mode                            |
| :----------| :----------------------------| :--------------------| ------------------------------------------|
| caesar    | Monoalphabetic Substitution | Integer             | Brute force                              |
| rot13     | Monoalphabetic Substitution | None                | -                                        |
| atbash    | Monoalphabetic Substitution | None                | -                                        |
| autokey   | Polyalphabetic Substitution | String              | Dictionary                               |
| vigenere  | Polyalphabetic Substitution | String              | Dictionary, Frequency Analysis (Kasiski) |
| beaufort  | Polyalphabetic Substitution | String              | Dictionary, Frequency Analysis (Kasiski)                               |
| railfence | Transposition               | Integer (must >= 2) | Brute force                              |

## Features

- Lightweight and Fast: Written in Pure C with zero external heavy dependencies.
- Stream-oriented design: Read from `stdin` with zero interactive prompt, Allowing seamless integration with other tools like `grep` or `awk`.
- Case-insensitive cipher names: Parameters like `-c Caesar` and `-c caesar` are processed identically.
- Dictionary attack for Autokey, Vigenere, and Beaufort cipher.
- Brute force attack for railfence and caesar cipher.

## License

MIT

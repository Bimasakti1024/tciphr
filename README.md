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

> tciphr -c <cipher> [-k <key>] [-d] [-C] [-v] [-l] [-p] [-h]

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

That example show a usage of tciphr to encode the text "the quick brown fox jumps over a lazy dog" using vigenere cipher with the key "secret".

You can also use another cipher, Like railfence cipher:

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

This example show how to work with files:

```bash
$ cat message.txt | tciphr -c rot13 > encoded.txt
```

Vigenere cipher and also with some other cipher can be broken by dictionary attack like this:
```bash
$ echo "bsog{fkewvr_pqyawozinf_otfiyr}" | tciphr -Cc vigenere -p wordlist.txt | grep flag
Cipherkey whoami: flag{tciphr_dictionary_attack}
$
```

The ciphertext "bsog{fkewvr_pqyawozinf_otfiyr}" are decoded using every cipherkey in `wordlist.txt`, The correct plaintext also have a recognizeable pattern ("flag") which the output can be piped to other tools like `grep`.

### Supported ciphers

| Cipher    | Category                    | Key requirement     | Cracking mode |
| :----------| :----------------------------| :--------------------| ---------------|
| caesar    | Monoalphabetic Substitution | Integer             | Brute force   |
| rot13     | Monoalphabetic Substitution | None                | -             |
| atbash    | Monoalphabetic Substitution | None                | -             |
| autokey   | Polyalphabetic Substitution | String              | Dictionary    |
| vigenere  | Polyalphabetic Substitution | String              | Dictionary    |
| beaufort  | Polyalphabetic Substitution | String              | Dictionary    |
| railfence | Transposition               | Integer (must >= 2) | Brute force   |

## Features

- Lightweight and Fast: Written in Pure C with zero external heavy dependencies.
- Stream-oriented design: Read from `stdin` with zero interactive prompt, Allowing seamless integration with other tools like `grep` or `awk`.
- Case-insensitive cipher names: Parameters like `-c Caesar` and `-c caesar` are processed identically.
- Dictionary attack for Autokey, Vigenere, and Beaufort cipher.
- Brute force attack for railfence and caesar cipher.

## License

MIT

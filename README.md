# tciphr

`tciphr` is a lightweight command-line interface to process text using historical cryptographic algorithms. It allows people like CTF player to process text through classic ciphers right from the terminal.

## Security Notice
This tool implement historical cryptographic algorithm which does not adhere to modern security standards.

## Usage

Usage: tciphr -c <cipher> [-k <key>] [-d] [-C] [-v] [-l] [-p] [-h]

`tciphr` operates as pipeline filter, It read text from `stdin` and output them to `stdout`.

### Example

```bash
$ echo "the quick brown fox jumps over a lazy dog" | tciphr -c vigenere -k secret
llg hybuo dispf jqo nnetu fzxj e nrdr vsi
$
```

That example show a usage of tciphr to encode the text "the quick brown fox jumps over a lazy dog" using vigenere cipher with the key "secret".

You can also use another cipher, Like rail-fence cipher:

```bash
$ echo "the quick brown fox jumps over a lazy dog" | tciphr -c railfence -k 3
tubnjsrzghqikrwfxupoeaayoecoomvld
$
```

This example show how to work with files:

```bash
$ cat message.txt | tciphr -c rot13 > encoded.txt
```

### Supported ciphers

| Cipher    | Category                    | Key requirement     |
| :----------| :----------------------------| :--------------------|
| Caesar    | Monoalphabetic Substitution | Integer             |
| rot13     | Monoalphabetic Substitution | None                |
| atbash    | Monoalphabetic Substitution | None                |
| autokey   | Monoalphabetic Substitution | String              |
| Vigenere  | Polyalphabetic Substitution | String              |
| beaufort  | Polyalphabetic Substitution | String              |
| railfence | Transposition               | Integer (must >= 2) |

## Features

- Lightweight and Fast: Written in Pure C with zero external heavy dependecies.
- Stream-oriented design: Read from `stdin` with zero interactive prompt, Allowing seamless integration with other tools like `grep` or `awk`.
- Case-insensitive cipher names: Parameters like `-c Caesar` and `-c caesar` are processed identically.
- Brute-force and Dictionary attack for some ciphers.

## License

MIT

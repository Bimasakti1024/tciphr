# Examples

This directory contains example files for demonstrating `tciphr` capabilities.

## Files

- `cap_excerpt.txt` — Excerpt from Crime and Punishment, used to demonstrate Kasiski examination.
- `wordlist.txt` — A wordlist for demonstrating dictionary attack.

# Usage

### Kasiski (Frequency Analysis)

```bash
$ cat cap_excerpt.txt | tciphr -c vigenere -k hello | tciphr -Cc vigenere -p strategy=kasiski,gram=3
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

### Dictionary Attack

```bash
$ echo "bsog{fkewvr_pqyawozinf_otfiyr}" | ./tciphr -Cc vigenere -p strategy=dictionary,wordlist=wordlist.txt
Cipherkey hello: uodv{rdalkd_imnpihvxcr_hpuxkk}
Cipherkey fox: werb{rnziym_bttmzjllir_rorltd}
Cipherkey password: mswo{jwntgr_xycmflkivn_sfofjr}
Cipherkey whoami: flag{tciphr_dictionary_attack}
Cipherkey onetwothree: nfkn{jwlpen_lclwdslpgo_kprvuy}
$
```

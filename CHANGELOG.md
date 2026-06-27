# Changelog

All notable changelog are documented in this file.

## [1.0.0] - 27-06-2026
### Added
- Kasiski examination (frequency analysis) strategy for vigenere cipher

### Changed
- `-p` flag now uses key=value syntax: `-p strategy=kasiski,gram=3` (breaking)

## Fixed
- readline_file skips last line when no trailing newline

## [0.3.0] - 13-06-2026
### Added
- Cracking mode for railfence and caesar cipher
- Dictionary attack for vigenere, autokey, and beaufort

### Changed
- Refactored `cipher_fn` from using `void` to `char *`

### Removed
- Non alphabetic character stripping from railfence cipher

## [0.2.0] - 30-05-2026
### Added
- Core engine support for autokey cipher.

## [0.1.0] - 29-05-2026
### Added
- Core engine support for caesar, atbash, vigenere, beaufort, rot13, and railfence cipher.
- Pipeline support

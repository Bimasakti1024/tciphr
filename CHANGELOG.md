# Changelog

All notable changelog are documented in this file.

## [UNRELEASED]
### Added
- Cracking mode for railfence and caesar cipher
- Dictionary attack for vigenere, autokey, and beaufort (WIP)

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

# [Rust](https://www.rust-lang.org/)

- [Docs.rs](https://docs.rs/)
- [rust-analyzer](https://rust-analyzer.github.io/)

```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh

rustc --version

rustup update
rustup self uninstall
```

```bash
rustc <file.rs>
rustc --cfg <flag> <file.rs>

RUST_BACKTRACE=1 <file>
RUST_BACKTRACE=full <file>
```

## [Cargo](https://doc.rust-lang.org/cargo/index.html)

```bash
cargo --version

cargo new <Project Name>
cargo fmt
cargo doc
```

### [mdBook](https://github.com/rust-lang/mdBook)

```bash
cargo install mdbook

mdbook build
```

## [Rustfmt](https://github.com/rust-lang/rustfmt)

```bash
rustfmt <file>
rustfmt --check <file>
```

## [Clippy](https://github.com/rust-lang/rust-clippy)

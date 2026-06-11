#include <iostream>
#include <string>
#include "Lexer.h"

int main() {
    std::string sourceCode = R"(use std::thread::sleep;
use std::time::Duration;
use std::io::{self, Write};
fn main() {
    let mut seconds = 5;
    println!("--- Rust Conteo Demo ---");
    while seconds > 0 {
        print!("\rTiempo que queda son: {} segundos... ", seconds);
        io::stdout().flush().unwrap();
        sleep(Duration::from_secs(1));
        seconds -= 1;
    }
    println!("\n\n Rust es seguro!");
})";

    std::string SegundoEjercicio = R"(use std::sync::atomic::{AtomicUsize, Ordering};
use std::sync::Arc;
use std::thread;
fn main() {
    let counter = Arc::new(AtomicUsize::new(0));
    let mut handles = vec![];
    println!("Empezando los 10 threads");
    for i in 0..10 {
        let counter_clone = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            for _ in 0..100 {
                counter_clone.fetch_add(1, Ordering::SeqCst);
            }
            println!("   Thread #{} termino de trabajar", i);
        });
        handles.push(handle);
    }
    for handle in handles {
        handle.join().unwrap();
    }
    println!("\n Al final se conto: {}", counter.load(Ordering::SeqCst));
})";
    Lexer lexer;
    std::vector<Token> tokens = lexer.tokenize(SegundoEjercicio);

    std::cout << "Tokens generated:\n";
    for (const auto& token : tokens) {
        std::cout << "Lexeme: '" << token.lexeme << "'\n";
    }

    return 0;
}

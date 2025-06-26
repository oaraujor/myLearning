#![allow(unused)]

use std::io; //importing libraries
use rand::Rng; // you have to specify vercion in the dependency section of cargo.toml
use std::io::{Write, BufReader, BufRead, ErrorKind};
use std::fs::File;
use std::cmp::Ordering;

fn main() { // functions start with fn <name> (params)
    println!("What is your name?"); //macro for printig lines on terminals
    //let mut name = String::new(); //all variables in Rust are inmutable, we use mut keyword to state that is a mutable variable
    //let greeting = "Nice to meet you."; //inmutable "static" variable | strings "" characters ''
    //io::stdin().read_line(&mut name).expect("Didn't Recieve Input"); //.expect is error handling built in

    //println!("Hello {}! {}", name.trim_end(), greeting); // {} to state variables to be places there

    const ONE_MIL: u32 = 1_000_000; //u32 unsigned int 32 bits
    const PI: f32 = 3.141592;//f32 float number 32bits
    let age = "47"; //strings "" char ''
    let mut age: u32 = age.trim().parse().expect("Age wasnt assigned a number"); //.parse converst some data types into other types
    age = age + 1; //since age is mut we can add
    println!("Im {} and i want ${}", age, ONE_MIL);

    let is_true = true; // true or false for boolen data types
    let my_grade = 'A'; //char tyoe declaration

    //math

    let num_1: f32 = 1.111111111111111;
    println!("f32: {}", num_1 + 0.111111111111111); //check precision of f point numbers
    let num_2: f64 = 1.111111111111111;
    println!("f64: {}", num_2 + 0.111111111111111); //check precision of f point numbers

    let mut num_3: u32 = 6;
    let num_4: u32 = 5;

    println!("6 + 5 = {}", num_3 + num_4);
    println!("6 - 5 = {}", num_3 - num_4);
    println!("6 * 5 = {}", num_3 * num_4);
    println!("6 / 5 = {}", num_3 / num_4);
    println!("6 % 5 = {}", num_3 % num_4);

    num_3 += 1; //same as C
    println!("num_3 + 1 = {}", num_3);

    //generate random values

    let rand_num = rand::rng().random_range(1..101);
    println!("Random number from 1-101: {}", rand_num);


}

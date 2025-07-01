#![allow(unused)]

use std::io;
use std::sync::atomic::spin_loop_hint; //importing libraries
use rand::Rng; // you have to specify vercion in the dependency section of cargo.toml
use std::io::{Write, BufReader, BufRead, ErrorKind};
use std::fs::File;
use std::cmp::Ordering;

fn main() { // functions start with fn <name> (params)
    println!("What is your name?"); //macro for printig lines on terminals
    let mut name = String::new(); //all variables in Rust are inmutable, we use mut keyword to state that is a mutable variable
    let greeting = "Nice to meet you."; //inmutable "static" variable | strings "" characters ''
    io::stdin().read_line(&mut name).expect("Didn't Recieve Input"); //.expect is error handling built in

    println!("Hello {}! {}", name.trim_end(), greeting); // {} to state variables to be places there

    const ONE_MIL: u32 = 1_000_000; //u32 unsigned int 32 bits
    const PI: f32 = 3.141592;//f32 float number 32bits
    let age = "47"; //strings "" char ''
    let mut age: u32 = age.trim().parse().expect("Age wasnt assigned a number"); //.parse converst some data types into other types
    age = age + 1; //since age is mut we can add
    println!("Im {} and i want ${}", age, ONE_MIL);

    let is_true = true; // true or false for boolen data types
    let my_grade = 'A'; //char tyoe declaration

    //math logic-----------------------------------------------------

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

    //generate random values-----------------------------------------------------

    let rand_num = rand::rng().random_range(1..101);
    println!("Random number from 1-101: {}", rand_num);

    //conditionals-----------------------------------------------------

    let age = 886;
    if (age >= 1) && (age <= 18){
        println!("age between 1 and 18 inclusive");
    } else if (age > 18) && (age <= 35){
        println!("age between 19 and 35");
    } else if (age == 36) || (age == 37){
        println!("age 36 or 37");
    } else{
        println!("age is above 38");
    }

    //we can also "map" values with an if statement directly on definition
    let mut my_age = 47;
    let can_vote = if my_age >= 18{
        true
    } else{
        false
    };
    println!("Can vote: {}", can_vote);

    //match-----------------------------------------------------
    let age2 = 25;
    match age2{
        1..=18 => println!("Underage"), // .. defines a range
        21 | 50 => println!("21 or 50"),// | or comparison
        65..=i32::MAX => println!("65 to max"), // 65 to the max value of an int32 value
        _ => println!("everything else") // _ defines the default value if neither of the other ones match
    };

    let age3 = 18;
    let voting_age = 18;
    // another match example with builtin functions
    match age3.cmp(&voting_age){ // .cmp() built in function to match | & reference to a variable
        Ordering::Less => println!("cant vote"), //from the ordering crate Less that &voting_age
        Ordering::Greater => println!("Able to vote"), //from the ordering crate Greater that &voting_age
        Ordering::Equal => println!("just enough to vote") //from the ordering crate Equal that &voting_age
    };

    //arrays-----------------------------------------------------
    let arr_1 = [1,2,3,4,5,6,7,8,9];
    println!("1st: {}", arr_1[0]);
    println!("len: {}", arr_1.len());

    let mut loop_idx = 0;
    loop {
        if arr_1[loop_idx] % 2 == 0{
            loop_idx += 1;
            continue;
        }
        if arr_1[loop_idx] == 9{
            break;
        }
        println!("Odd val: {}", arr_1[loop_idx]);
        loop_idx += 1;
    }

    // while loop-----------------------------------------------------
    
    let mut loop_idx = 0;
    while loop_idx < arr_1.len(){
        println!("Array value {}: {}", loop_idx, arr_1[loop_idx]);
        loop_idx += 1;
    }

    //for loops-----------------------------------------------------

    for val in arr_1.iter(){ //.iter() function to itrerate through values in the array
        println!("Val: {}", val);
    }

    //tuples-----------------------------------------------------

    let my_tuple: (u8, String, f64) = (47, "Derek".to_string(), 50_000.00);

    println!("Name: {}", my_tuple.1); //print value by referencing with .1
    let (v1,v2,v3) = my_tuple; //asigning data from one tuple to another
    println!("Age: {}", v1);

    //strings-----------------------------------------------------
    // 2 types of strings
    // String  - vector of bytes that can be changed
    // &str - point to string and allows veiwing of strings

    let mut st1 = String::new(); //intializying new string mut variable, curr empty
    st1.push('A'); //we "add" into st1
    println!("{}", st1);

    st1.push_str(" BCDE"); // we concatenate a new string

    println!("{}", st1);

    for word in st1.split_whitespace(){ //iterator for string that delimits each word by a space
        println!("{}", word);
    }
    
    let st2 = st1.replace("A", "Another"); // assing the st1 to st1 but replacing A wioth another string using .replace
    println!("{}", st2);
    
    let st3 = String::from("x h g t y g f x f x"); //creates a growable, heap allocated stri, which we can modify it, pass it arround and free it when done
    let mut v1: Vec<char> = st3.chars().collect(); //takes the string st3 and splits it into its individual charcters and collects them into a vector of chars
    v1.sort(); //sorts the vector
    v1.dedup(); //removes consecutive elements
    for char in v1{
        println!("{}", char);
    }

    let st4: &str = "Random_String";
    let mut st5: String = st4.to_string(); //heap allocated string made from st4
    println!("st5: {}", st5);
    
    let byte_arr_1 = st5.as_bytes(); //convert a string to an array of bytes
    for char2 in byte_arr_1{
        println!("byte_arr_1: {}", char2);
    }
    let st6 = &st5[0..6]; //creates st6 from st5 from indexes 0 to 6
    println!("st6: {}",st6);
    println!("String Len: {}", st6.len());
    
    st5.clear();//clears st5
    println!("st5: {}", st5);

    let st7 = String::from("Just Some"); //heap allocated String
    let st8 = String::from("Words in ABC"); //heap allocated String

    let st9 = st7.clone() + &st8;
        // Concatenate st7 and st8 into a new String (st9).
        // st7 is cloned to preserve ownership, since using '+' would otherwise move st7.
        // st8 is passed as a string slice (&st8) to avoid moving it.

    println!("st7: {} + st8: {} -> st9: {}", st7, st8, st9);

    //Type casting -----------------------------------------------------

    let int_u8: u8 = 5;
    let int2_u8: u8 = 4;

    let int3_u32: u32 = (int_u8 as u32) + (int2_u8 as u32); //converting from unsigned 8bits to 32 bits

    // enums ------------------------------------------------------------
    enum Days{ //enum just like in C
        Monday,
        Tuesday,
        Wednesday,
        Thursday,
        Friday,
        Saturday,
        Sunday
    }

    impl Days { //we can implement "functions" to types like enums
        fn is_weekend(&self) -> bool { // declaring a function with output bool type
            match self {
                Days::Saturday | Days::Sunday => true,
                _ => false
            }
        }
    }

    let day: Days = Days::Monday; //declare day type
    println!("is weekend: {}", day.is_weekend()); // use the function

    //vectors ----------------------------------------------------
    //they are like arrays that can grow if mut, they only store things of the same types

    let vec1: Vec<i32> = Vec::new(); //declaring a new vector
    vec1.push(44);

}

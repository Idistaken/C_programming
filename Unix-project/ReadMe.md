# Project Description :
This project will have three parts:

## Part 1 :
A tie up will be made between a single server and multiple clients at
the same time. Here we have used concept of pthread to write a concurrent server under UNIX to handle each client.

## Part 2 :
The 2nd part of the project is to encrypt data between server and
clients. In our project we will use AES Symmetric Key encryption method to
encrypt data from sender client to receiver client and vice versa. The AES has a symmetric
key which has already been shared amoung all clients . The same symmetric key will be used to encrypt and decrypt data amoung cliens.

## Part 3 : 
The 3rd part of the project preserves integrity of data amoung all clients. In this part each client computes a hash of data using a popular hashing method MD5. All the data from Sender client to Receiver client will be hashed. Receiver client  will check the received hash value againt hashed value from the decrypted text before accepting the data.

## Steps -
1. Establish a concurrent server which can handle multiple clients using fork simultaneously.
2. Clients will use a symmetric key to encrypt the data (plain text) using AES.
3. Clients will compute a hash of data (plain text) and the hashed value of data will be placed in a buffer along with the encrypted data (cipher text).
4. The buffer will be sent to the server
5. The server receives the buffer and forwards it to the receiver client .
6. The cipher text will be decrypted using the same symmetric key with other clients .
7. The hash will be computed from decrypted data (plain text) at the receiver client .
8. If the sent Hash(step 3) from clients and computed hash at receiver client (step 7 ) are matched , then it will be printed at the receiver client terminal .

## How to Run Program :
1. Compile Server with Command :
gcc -pthread gmult.c aes.c mainAES.c md5.c Server.c -o demoServer -w
2. Run Server with Command :
./demoServer
3. Run Compile Client with Command :
gcc -pthread gmult.c aes.c mainAES.c md5.c Client.c -o demoClient -w
4. Run Client with Command :
./demoClient
5. Now you can connect as many clients as you want just by running
./demoClient in the new terminal .

<p align="center">
  <img src="Screenshot 2021-02-05 at 8.59.45 PM.png" height="250" width="300">
</p>

## Showing sending and receiving of text with encryption and hashing
<p align="center">
  <img src="Screenshot 2021-01-23 at 1.11.52 PM.png" height="400" width="700">
</p>

## Sending and Receiving of text between two client (client 1 & client 2 )
<p align="center">
  <img src="Screenshot 2021-01-23 at 3.42.01 PM.png" height="400" width="700">
</p>
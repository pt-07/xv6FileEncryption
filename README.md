After cloning the repository, you can run the following commands in a linux based OS to get xv6 up and running and check out the encryption and decryption of a file (in this case README)
cd xv6-public
make 
make qemu-nox
encrypt <password> README
#you can check the encrypted README with cat README
decrypt <password> README 
#then again check the README to view the decrypted version with cat README

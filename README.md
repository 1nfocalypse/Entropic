<p align="center">
  <a href="https://github.com/1nfocalypse/Entropic">
	<img alt="Entropic" src="https://i.imgur.com/Iy0tXFx.png"/>
  </a>
</p>
<p align="center">
  <a href="https://choosealicense.com/licenses/gpl-3.0/">
  	<img alt="License: GPL-3.0" src="https://img.shields.io/github/license/1nfocalypse/Entropic"/>
  </a>
</p>
<h2 align="center">Entropic</h3>
<h3 align="center">
  A Toy Viginere Cipher Implementation
</h2>
<p align="center">
  By <a href="https://github.com/1nfocalypse">1nfocalypse</a>
</p>

# What is it?
Entropic is a toy implementation of a Viginère Cipher. Viginère Ciphers are a polyalphabetic cipher dating back to the 1500s, and remained unbroken for approximately three centuries afterwards. They were broken via a method called
Kasiski analysis, which utlized the characteristic of a repeated key over a large enough bit of ciphertext to find patterns, from which information could be further enumerated. More on Kasiski analysis can be found [here](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher#Kasiski_examination).
While these ciphers are vulnerable when used with a block key, they retain unbroken in the context of Vernam One Time Pads, which are randomly generated keys that stretch the entire length of the cleartext. Since the key is never repeated
and is truly random, Kasiski analysis fails. A simulation of a Vernam One-Time Pad can be found implemented here, however, does not possess the same characteristics, as the string is pseudorandomly generated via a Mersenne Twister.
Alternatively, if a user is sufficiently capable of producing a truly random string, then they could utilize it as a custom key within the program to obtain a legitimate One-Time Pad. However, this is not encouraged, as there are markedly
superior ways of performing symmetric encryption in the modern era. For more information on Viginère Ciphers and other cryptographic schemes, please be sure to check out my writeup on mathematical cryptography, which can be found
[here](https://github.com/1nfocalypse/CryptoWriteup). 

# Contributing
If you would like to submit a PR, please feel free to do so. There are very likely some bugs hiding in here that I didn't sniff out. If you choose to submit a PR, please explain your changes and I'll be happy to review it. Thank you!

# Disclaimer
Viginère Ciphers are outdated, and this is an educational toy. While it has the capacity to encrypt and decrypt messages, it is not meant for serious use. Please consider alternative cryptosystems, such as AES, for contemporary needs.
By using this software, you acknowledge that neither I nor any contributors are responsible for any losses or damage that may occur. For more information, please consult the license, which can be found [here](LICENSE).

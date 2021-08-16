# COMP 232 - Bison and Flex

In this lab, we will be using **flex** to build a lexer via regular expressions and **bison** to parse the sequence of tokens output by said lexer.

Before you start, you will want to install flex and bison:

* Mac: `brew install flex bison`
* WSL: in the Ubuntu console, `sudo apt-get install -y flex bison`

`sudo apt-get install -y flex bison` will work on Linux distributions in general, if you're not using one of the two above.

When flex and bison are installed, you're ready to start learning flex via the [flex project](./flex), whose instructions are located in [flex/flex.md](./flex/flex.md).

After you've finished the flex project, you're ready to learn to use bison and flex together; open the [bison project](./bison) and follow the instructions in [bison/bison.md](./bison/bison.md) to complete it.

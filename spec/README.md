# TLA+ Model

This directory contains the TLA+ project that defines the model for the source. \
In order to use an IDE such as [TLA+ toolbox](https://lamport.azurewebsites.net/tla/toolbox.html) is needed. You can also use vscode with the TLA+ plugin. 

To verify the model, open the main.tla, add model and in the model overview, assign to the model values VALUE->{1}, set NULL to be a "Model value" by checking the box.

Add the properties the invariants HasFirst, HasLast ... (everything under invariants in main.tla) \

After this the model should run and pass.

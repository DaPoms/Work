PRJ = $(notdir $(patsubst %/,%, $(realpath .)))
PKG = fiveCard

SRC =\
	src/$(PKG)/Card.java\
	src/$(PKG)/Deck.java\
	src/$(PKG)/Hand.java\
	src/$(PKG)/Game.java\
	src/$(PKG)/CmdLineInput.java

BIN =\
	build/$(PKG)/Card.class\
	build/$(PKG)/Shoe.class\
	build/$(PKG)/Hand.class\
	build/$(PKG)/Game.class\
	build/$(PKG)/CmdLineInput.class

.PHONY: all clean
all: $(BIN)

$(BIN): $(SRC) | build
	@javac -d build src/$(PKG)/*.java
	@echo "PLEASE IGNORE THE TIME SKEW WARNING. YOUR BUILD WAS SUCCESSFUL, I PROMISE. UNIX JUST HATES ME"

build:
	@mkdir -p $@

clean:
	@rm -rf build
	@rm -rf src/$(PKG)/*.java~

run: $(BIN)
	@java -cp build $(PKG).Game $(ARGS)

submit: clean
	@cd ..; jar cf $(PRJ).jar -C $(PRJ) .
	@cd ..; /export/home/public/gnye/cpsc243/turnin/turnin-Project $(PRJ).jar


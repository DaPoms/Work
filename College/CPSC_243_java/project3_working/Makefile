PRJ = $(notdir $(patsubst %/,%, $(realpath .)))
PKG = fiveCard
DEBUG = -g

SRC =\
	src/$(PKG)/Card.java\
	src/$(PKG)/Deck.java\
	src/$(PKG)/Hand.java\
	src/$(PKG)/PokerGame.java\
	src/$(PKG)/PokerHand.java\
	src/$(PKG)/PokerException.java\
	src/$(PKG)/CmdLineInput.java

BIN =\
	build/$(PKG)/Card.class\
	build/$(PKG)/Deck.class\
	build/$(PKG)/Hand.class\
	build/$(PKG)/PokerGame.class\
	build/$(PKG)/PokerHand.class\
	build/$(PKG)/PokerException.class\
	build/$(PKG)/CmdLineInput.class\

.PHONY: all clean

all: $(BIN)

$(BIN): $(SRC) | build
	@javac -d build src/$(PKG)/*.java $(DEBUG)
	@echo "PLEASE IGNORE THE TIME SKEW WARNING. YOUR BUILD WAS SUCCESSFUL, I PROMISE. UNIX JUST HATES ME"

build:
	@mkdir -p $@

clean:
	@rm -rf build
	@rm -rf src/$(PKG)/*.java~

run: $(BIN)
	@java -cp build $(PKG).PokerGame $(ARGS)

submit: clean
	@cd ..; jar cf $(PRJ).jar -C $(PRJ) .
	@cd ..; /export/home/public/gnye/cpsc243/turnin/turnin-Project $(PRJ).jar


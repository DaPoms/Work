PRJ = $(notdir $(patsubst %/,%, $(realpath .)))
PKG = fiveCard
DEBUG = -g

SRC =\
	src/$(PKG)/Card.java\
	src/$(PKG)/Deck.java\
	src/$(PKG)/Hand.java\
	src/$(PKG)/PokerCasinoGame.java\
	src/$(PKG)/PokerHand.java\
	src/$(PKG)/PokerException.java\
	src/$(PKG)/CmdLineInput.java\
	src/$(PKG)/CasinoCardGame.java\
	src/$(PKG)/Bettor.java


BIN =\
	build/$(PKG)/Card.class\
	build/$(PKG)/Deck.class\
	build/$(PKG)/Hand.class\
	build/$(PKG)/PokerCasinoGame.class\
	build/$(PKG)/PokerHand.class\
	build/$(PKG)/PokerException.class\
	build/$(PKG)/CmdLineInput.class\
	build/$(PKG)/CasinoCardGame.class\
	build/$(PKG)/Bettor.class

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

doc:
	@javadoc -d docs -sourcepath src $(PKG)

run: $(BIN)
	@java -cp build $(PKG).PokerCasinoGame $(ARGS)

submit: clean
	@cd ..; jar cf $(PRJ).jar -C $(PRJ) .
	@cd ..; /export/home/public/gnye/cpsc243/turnin/turnin-Project $(PRJ).jar


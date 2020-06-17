DOCKER_FILE := build.Dockerfile
NAME := idea-nginx-support
VERSION := 0.1.9-fic
TAG := $(NAME)-$(VERSION)
ZIP:= $(NAME)-$(VERSION).zip
OUT_DIR:= dist

fetch : build
	{  \
		CID=$$(docker create $(TAG)); \
		mkdir -p $(OUT_DIR); \
		docker cp $$CID:/build/build/distributions/$(ZIP)  $(OUT_DIR)/$(ZIP); \
		docker rm -v $$CID; \
		ls -lah $(OUT_DIR); \
		\
	}

build:
	time docker build -f $(DOCKER_FILE) -t $(TAG) .

clean:
	rm *.zip

.PHONY: clean build
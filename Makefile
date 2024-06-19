.PHONY:
	build run

build:
	docker build -t my-python-app .

run:
	docker run -v $(CURDIR):/app -it --cpus=1 -m=500m my-python-app
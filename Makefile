build:
	docker build -t my-python-app .

run:
	docker run -v $(CURDIR):/app -it --cpus=1 -m=1000m my-python-app

run-2:
	docker run -v $(CURDIR):/app -it my-python-app
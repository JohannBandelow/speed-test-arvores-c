build:
	docker build -t my-python-app .

run:
	docker run -v $(CURDIR):/app -it my-python-app
# Use a imagem oficial do Python como base
FROM python:3.8

# Defina o diretório de trabalho no container
WORKDIR /app

# Copie o arquivo main.py para o diretório de trabalho atual (no container)
COPY main.py .

RUN pip install matplotlib

# Execute o script Python quando o container for iniciado
CMD ["python", "./main.py"]
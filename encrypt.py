import io

def crypt(s, key):
    return bytes(x ^ key for x in s)

def main():
    data = io.open('python.zip', 'rb').read()
    data = crypt(data, 0x6A)
    out = io.open('python.zip.enc', 'wb')
    out.write(data)
    out.close()

if __name__ == '__main__':
    main()

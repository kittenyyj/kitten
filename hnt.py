def hnt(n,a,b,c):
    if n==1:
        print(a,"-->",c)
        return None
    if n==2:
        print(a,"-->",b)
        print(a,"-->",c)
        print(b,"-->",c)
        return None
    hnt(n-1,a,c,b)
    print(a,"-->",c)
    hnt(n-1,b,a,c)
a="A"
b="B"
c="C"
hnt(10,a,b,c)

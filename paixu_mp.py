a=[8,2,4,9,7,6,5,3]
b=len(a)
for i in range(1,b):
    for j in range(1,b-i+1):
        if a[j-1]>a[j]:
            t=a[j-1]
            a[j-1]=a[j]
            a[j]=t
print(a)

obj=oauth_nonce
$(obj):$(obj).o
	gcc -o $(obj)1 $(obj).o
	gcc -o $(obj)2 $(obj).o -static
$(obj).o:$(obj).s
	gcc -c $(obj).s
$(obj).s:$(obj).c
	gcc -S $(obj).c -g
clean:
	rm -f $(obj).o $(obj).s

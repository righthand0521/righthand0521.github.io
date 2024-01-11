# [busybox](https://busybox.net/)

## [Download Binaries](https://busybox.net/downloads/binaries/)

<details><summary>busybox_SENDMAIL</summary>

``` bash
echo "Test" | ./busybox_SENDMAIL -f <mail address> -t <mail address> -S msa.hinet.net
echo -e "Subject: Test\nHello, world." | ./busybox_SENDMAIL -f <mail address> -t <mail address> -S msa.hinet.net
```

</details>

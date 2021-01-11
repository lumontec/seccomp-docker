FROM ubuntu:latest
RUN apt update

RUN apt install -y auditd sysdig strace

RUN mkdir /test
ADD ./copy_file_range /test
RUN chmod +x /test/copy_file_range
ADD ./src /test/src
ADD ./dst /test/dst

CMD echo "chmod copy_file_range:" && \
	chmod +x /test/copy_file_range && \
	echo "running copy_file_range:" && \
	/test/copy_file_range /test/src /test/dst && \
	echo "cat src:" && \
	cat /test/src && \
	echo "cat dst:" && \
	cat /test/dst && \
	dmesg | grep copy_file_range

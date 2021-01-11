# Secomp docker tests

Secomp allows for coarse grained syscall filtering, policies can be defined but do nota allow for syscall arguments inspection. This implies that filtering can realistically only happen based on syscall type.
Kubernetes supports a simple api for restricting containers seccomp profiles.

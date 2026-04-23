*This project has been created as part of the 42 curriculum by [dhontani].*

# 🖥️ Born2beRoot

## Description

Born2beRoot is a system administration project from the 42 curriculum. The goal is to set up a secure Linux virtual machine from scratch, applying real-world server hardening practices: encrypted partitions, strict password policies, firewall configuration, SSH access control, automated monitoring, and sudo restrictions.

The project is intentionally minimal — no graphical interface, no unnecessary packages. Every configuration choice must be deliberate and justifiable.

### Operating System Choice: Debian

This project was completed using **Debian GNU/Linux**. The choice between Debian and Rocky Linux comes down to background and goals:

| | Debian | Rocky Linux |
|---|---|---|
| **Base** | Independent | RHEL-based |
| **Package manager** | apt / dpkg | dnf / rpm |
| **Security module** | AppArmor | SELinux |
| **Learning curve** | Lower | Higher |
| **Target audience** | General purpose, servers, embedded | Enterprise servers |
| **Release cycle** | Stable, slow-moving | Follows RHEL releases |
| **Community** | Very large, long-standing | Growing, enterprise-focused |

**Why Debian:** It has a gentler learning curve, excellent documentation, and is the recommended option in the subject for first-time users. Its package ecosystem is mature and its stability is well proven.

**Why not Rocky:** Rocky Linux (a community rebuild of RHEL) is more representative of enterprise production environments, but its stricter SELinux policies and rpm-based tooling add complexity that is harder to justify at this stage.

---

### Main Design Choices

**Partitioning**

The disk is partitioned using LVM (Logical Volume Manager) with full encryption via LUKS. LVM adds a layer of abstraction over physical partitions, making storage management flexible without repartitioning. Encryption ensures data is unreadable without the passphrase, even if the physical disk is accessed directly.

```
sda1  →  /boot       (unencrypted, required for GRUB to boot)
sda5  →  LUKS encrypted → LVM
              ├── root  →  /
              └── home  →  /home
```

`/boot` is intentionally kept outside the encrypted volume because GRUB needs to read kernel files before the passphrase can be entered.

**Security policies**

- Password expiration every 30 days, minimum 2 days between changes
- Passwords require at least 10 characters, 1 uppercase, 1 digit, no username, max 3 consecutive identical characters
- sudo limited to 3 password attempts, custom error message, full input/output logging, TTY required
- SSH root login disabled, access restricted to port 4242
- UFW firewall active, only port 4242 allowed

**User management**

- Root account exists but cannot be accessed via SSH
- A personal user (42 login) belongs to both `sudo` and `user42` groups
- All new users are subject to the password policy defined in `/etc/login.defs` and `/etc/pam.d/common-password`

**Services installed**

- `openssh-server` — remote access via SSH on port 4242
- `ufw` — firewall management
- `sudo` — controlled privilege escalation with full audit logging
- `libpam-pwquality` — password complexity enforcement
- Custom monitoring script executed every 10 minutes via cron

---

### Technology Comparisons

**AppArmor vs SELinux**

Both are Linux Security Modules (LSM) that implement Mandatory Access Control (MAC), restricting what processes can do regardless of user permissions.

| | AppArmor | SELinux |
|---|---|---|
| **Used by** | Debian, Ubuntu | Rocky, Fedora, RHEL |
| **Model** | Path-based profiles | Label-based policies |
| **Complexity** | Lower, easier to configure | Higher, more granular |
| **Default mode** | Enforce or complain | Enforcing or permissive |
| **Auditability** | Good | Excellent |

AppArmor ships with Debian and is active by default. It restricts programs based on per-application profiles. SELinux is more powerful but significantly harder to configure and debug, which is why it tends to be the standard in enterprise RHEL-based environments.

**UFW vs firewalld**

Both are frontends for the kernel's netfilter/iptables system.

| | UFW | firewalld |
|---|---|---|
| **Used by** | Debian, Ubuntu | Rocky, Fedora, RHEL |
| **Interface** | Simple CLI | CLI + zones concept |
| **Complexity** | Very low | Moderate |
| **Dynamic rules** | No (requires reload) | Yes |
| **Use case** | Simple servers, personal machines | Complex network environments |

UFW (Uncomplicated Firewall) lives up to its name — a handful of commands cover most use cases. firewalld introduces the concept of zones (sets of rules applied to network interfaces), which is more powerful but overkill for a single-interface server like this one.

**VirtualBox vs UTM**

| | VirtualBox | UTM |
|---|---|---|
| **Platform** | Windows, macOS, Linux | macOS only |
| **Architecture** | x86/x64 | x86/x64 + ARM (Apple Silicon) |
| **License** | Free (Oracle) | Free (open source) |
| **Performance on Apple Silicon** | Poor (requires emulation) | Native on M1/M2/M3 |
| **Subject requirement** | Mandatory (unless unavailable) | Alternative for Apple Silicon |

VirtualBox is the required option per the subject. UTM is the alternative for campuses where VirtualBox is unavailable, typically due to Apple Silicon machines where x86 emulation makes VirtualBox impractically slow. UTM uses QEMU under the hood and runs natively on ARM.

---

## Instructions

### Requirements

- VirtualBox (or UTM on Apple Silicon)
- Debian ISO — download from [debian.org](https://www.debian.org)
- At least 12 GB of free disk space (30 GB for bonus)

### Verifying the machine signature

The submitted `signature.txt` contains the SHA-1 hash of the virtual disk file (`.vdi`). To verify it matches:

```bash
shasum yourmachine.vdi
```

Compare the output with the contents of `signature.txt`. They must be identical.

> ⚠️ Never boot the original VM after generating the signature. Always work on a clone for evaluations.

### Connecting via SSH

```bash
ssh your_login@localhost -p 4242
```

Make sure the port forwarding rule in VirtualBox maps port 4242 (guest) to an available port on the host.

### Checking service status

```bash
# Firewall
sudo ufw status

# SSH
sudo service ssh status

# Cron (monitoring script)
sudo crontab -u root -l

# Partitions and LVM
lsblk
```

### Running the monitoring script manually

```bash
bash /path/to/monitoring.sh
```

---

## Resources

### Documentation

- [Debian Official Documentation](https://www.debian.org/doc/)
- [Debian Administrator's Handbook](https://www.debian.org/doc/manuals/debian-handbook/)
- [Linux man pages online](https://man7.org/linux/man-pages/)
- [UFW documentation](https://help.ubuntu.com/community/UFW)
- [OpenSSH documentation](https://www.openssh.com/manual.html)
- [LVM2 Resource Page](https://sourceware.org/lvm2/)
- [PAM documentation](http://www.linux-pam.org/Linux-PAM-html/)
- [AppArmor wiki](https://gitlab.com/apparmor/apparmor/-/wikis/home)

### Tutorials

- [gemartin99 — Born2beRoot Tutorial](https://github.com/gemartin99/Born2beroot-Tutorial) — the main reference used for this setup
- [pasqualerossi — Born2BeRoot Guide](https://github.com/pasqualerossi/Born2BeRoot-Guide)

### AI Usage

AI tools were used as a learning aid to better understand concepts and commands encountered during the project:

- **Understanding commands** — breaking down the purpose and syntax of commands used throughout the setup (awk, lsblk, journalctl, vmstat, df, etc.)
- **Conceptual clarification** — explaining underlying concepts such as LVM, LUKS encryption, PAM, TTY, MBR partition schemes, and how layers like crypt and LVM relate to physical partitions
- **No code was generated by AI** — all configuration files, scripts, and commands were written and executed manually following the subject requirements

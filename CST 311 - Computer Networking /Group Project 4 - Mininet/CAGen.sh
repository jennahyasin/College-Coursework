 #!/bin/bash

# CAGen.sh for CST311 @ CSUMB by BayTech: Luis Jimenez-Barrios, 
#   Warren Ngoun, Yukio Rivera, Jennah Yasin.
# A Bash script that generates a CA for the matching sslserver.py.

COUNTRY_NAME="US"
STATE="CA"
LOCALITY="Monterey"
ORG_NAME="SCD"
ORG_NAME_2="CST311"
ORG_UNIT="CST311"
ORG_UNIT_2="Networking"
COMMON_NAME="ca.webpa4.test"
COMMON_NAME_2="www.webpa4.test"
EMAIL=""
CHALLENGE=""
COMPANY=""

# Assumes /demoCA and all needed folders exist already like /private
cd /etc/ssl/demoCA/
# Genereate CA's RSA Private Key
sudo openssl genrsa -aes256 -out privateKeyPA4.pem -passout pass:test 2048

# Create ROOT CA cert. Auto inputs all needed fields like password (just 
# "test") and the needed country and org names, etc. 
cat << __EOF__ | sudo openssl req -x509 -new -nodes -key privateKeyPA4.pem -sha256 -days 1825 -out PA4cert.pem -passin pass:test
$COUNTRY_NAME
$STATE
$LOCALITY
$ORG_NAME
$ORG_UNIT
$COMMON_NAME
$EMAIL
__EOF__

# Print out the cert (useful for Debugging)
# Encrypted version
cat PA4cert.pem
# Decrypted version
sudo openssl x509 -text -noout -in /etc/ssl/demoCA/PA4cert.pem

# Install Root CA to Mininet VM private store
sudo mv ./privateKeyPA4.pem ./private

# Update & Install CA-certs to move our cert to the right location
sudo apt-get update
sudo apt-get install -y ca-certificates
# Now copy cert to dir that ca-certs will work on & change ext
sudo cp PA4cert.pem /usr/local/share/ca-certificates/PA4cert.crt
# Finally run the app
sudo update-ca-certificates

# Generate new RSA private key for SERVER 
sudo openssl genrsa -out www.webpa4.test-key.pem -passout pass:test 2048

# Forcibly reinstall needed certs
sudo apt-get install --reinstall ca-certificates
sudo apt-get -f install
sudo dpkg --purge --force-depends ca-certificates
yes | sudo apt-get -f install

# Now generate a request to the root CA and fill it w/ input
cat << __EOF__ | sudo openssl req -nodes -new -config /etc/ssl/openssl.cnf -key www.webpa4.test-key.pem -out www.webpa4.test.csr
$COUNTRY_NAME
$STATE
$LOCALITY
$ORG_NAME_2
$ORG_UNIT_2
$COMMON_NAME_2
$EMAIL
$CHALLENGE
$COMPANY
__EOF__

# Use Root CA to create the SERVER's cert
sudo openssl x509 -req -days 365 -in www.webpa4.test.csr -CA PA4cert.pem -CAkey ./private/privateKeyPA4.pem -CAcreateserial -out www.webpa4.test-cert.pem -passin pass:test

# Display the decrypted server CA
sudo openssl x509 -text -noout -in www.webpa4.test-cert.pem

# Copy server cert & key to right folders
sudo mv www.webpa4.test-cert.pem newcerts
sudo mv www.webpa4.test-key.pem private

# Add IPs to /etc/hosts
sudo sed -i '1s/^/10.0.1.3    www.webpa4.test \n/' /etc/hosts

echo "Done with Certificate Generation."
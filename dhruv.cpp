1. HAMMING CODE (C++)
Save as hamming.cpp and compile with: g++ hamming.cpp -o hamming

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;
int main(){
 string data;
 cout << "Enter data bits: ";
 cin >> data;
 for(char c:data){if(c!='0'&&c!='1'){cout << "Invalid data bits!" << endl;return 0;}}
 int m=data.length(),r=0;
 while(pow(2,r)<m+r+1)r++;
 int n=m+r;
 vector<int> code(n+1,0);
 int j=0;
 for(int i=1;i<=n;i++)if((i&(i-1))!=0)code[i]=data[j++]-'0';
 for(int i=0;i<r;i++){
  int p=1<<i,parity=0;
  for(int k=1;k<=n;k++)if(k&p)parity^=code[k];
  code[p]=parity;
 }
 cout << "Hamming Code: ";
 for(int i=1;i<=n;i++)cout << code[i];
 cout << endl;
 int errorPos;
 cout << "Enter error position (1-" << n << ", 0 for no error): ";
 cin >> errorPos;
 if(errorPos<0||errorPos>n){cout << "Invalid error position!" << endl;return 0;}
 if(errorPos!=0)code[errorPos]^=1;
 cout << "Received Code: ";
 for(int i=1;i<=n;i++)cout << code[i];
 cout << endl;
 int syndrome=0;
 for(int i=0;i<r;i++){
  int p=1<<i,parity=0;
  for(int k=1;k<=n;k++)if(k&p)parity^=code[k];
  if(parity)syndrome+=p;
 }
 if(syndrome==0)cout << "No error detected." << endl;
 else if(syndrome>n)cout << "Invalid syndrome; error cannot be corrected." << endl;
 else{
  cout << "Error detected at position: " << syndrome << endl;
  code[syndrome]^=1;
  cout << "Corrected Code: ";
  for(int i=1;i<=n;i++)cout << code[i];
  cout << endl;
 }
 return 0;
}

2. SUBNETTING (C++)
Save as subnetting.cpp and compile with: g++ subnetting.cpp -o subnetting

#include <iostream>
#include <string>
using namespace std;
int main(){
 string ip="192.168.1.0";
 int originalPrefix=24,requiredSubnets=2,borrowedBits=0;
 while((1<<borrowedBits)<requiredSubnets)borrowedBits++;
 int newPrefix=originalPrefix+borrowedBits;
 int hostBits=32-newPrefix;
 int totalHosts=1<<hostBits;
 int usableHosts=totalHosts-2;
 cout << "Original Network: " << ip << "/" << originalPrefix << endl;
 cout << "Number of Subnets: " << requiredSubnets << endl;
 cout << "New Prefix: /" << newPrefix << endl;
 cout << "Subnet Mask: 255.255.255.128" << endl;
 cout << "Usable Hosts per Subnet: " << usableHosts << endl;
 cout << "\nSubnet 1:" << endl;
 cout << "Network Address: 192.168.1.0" << endl;
 cout << "First Usable IP: 192.168.1.1" << endl;
 cout << "Last Usable IP: 192.168.1.126" << endl;
 cout << "Broadcast Address: 192.168.1.127" << endl;
 cout << "\nSubnet 2:" << endl;
 cout << "Network Address: 192.168.1.128" << endl;
 cout << "First Usable IP: 192.168.1.129" << endl;
 cout << "Last Usable IP: 192.168.1.254" << endl;
 cout << "Broadcast Address: 192.168.1.255" << endl;
 return 0;
}

3. DISTANCE VECTOR ROUTING (C++)
Save as distance_vector.cpp and compile with: g++ distance_vector.cpp -o distance_vector

#include <iostream>
using namespace std;
const int INF=9999;
int main(){
 int n;
 cout << "Enter number of routers (maximum 10): ";
 cin >> n;
 if(n<1||n>10){cout << "Invalid number of routers!" << endl;return 0;}
 int cost[10][10],dist[10][10];
 cout << "Enter cost matrix (9999 for no direct link):\n";
 for(int i=0;i<n;i++)for(int j=0;j<n;j++){cin >> cost[i][j];dist[i][j]=cost[i][j];}
 for(int i=0;i<n;i++)dist[i][i]=0;
 bool changed=true;
 while(changed){
  changed=false;
  for(int i=0;i<n;i++)for(int j=0;j<n;j++)for(int k=0;k<n;k++){
   if(dist[i][k]!=INF&&cost[k][j]!=INF&&dist[i][j]>dist[i][k]+cost[k][j]){
    dist[i][j]=dist[i][k]+cost[k][j];
    changed=true;
   }
  }
 }
 for(int i=0;i<n;i++){
  cout << "\nRouting table for Router " << i+1 << ":\n";
  cout << "Destination\tCost\n";
  for(int j=0;j<n;j++)if(dist[i][j]==INF)cout << j+1 << "\t\tUnreachable\n";else cout << j+1 << "\t\t" << dist[i][j] << "\n";
 }
 return 0;
}

4. TCP SOCKET MESSAGE PROGRAM
Save server as server.py and client as client.py. Run server first.

SERVER (server.py)
import socket
server=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server.bind(("127.0.0.1",5000))
server.listen(1)
print("Server is waiting for client...")
conn,addr=server.accept()
print("Client connected:",addr)
message=conn.recv(1024).decode()
print("Message received:",message)
conn.close()
server.close()

CLIENT (client.py)
import socket
client=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
client.connect(("127.0.0.1",5000))
message=input("Enter message: ")
client.sendall(message.encode())
client.close()

5. TCP SOCKET ARITHMETIC CALCULATOR
Save server as server.py and client as client.py. Run server first.

SERVER (server.py)
import socket
server=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server.bind(("127.0.0.1",8080))
server.listen(1)
print("Server waiting for client...")
conn,addr=server.accept()
print("Client connected:",addr)
data=conn.recv(1024).decode()
a,op,b=data.split()
a,b=float(a),float(b)
if op=="+":
 result=a+b
elif op=="-":
 result=a-b
elif op=="*":
 result=a*b
elif op=="/":
 result="Error: Division by zero" if b==0 else a/b
else:
 result="Invalid operator"
conn.sendall(str(result).encode())
print("Result sent:",result)
conn.close()
server.close()

CLIENT (client.py)
import socket
client=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
client.connect(("127.0.0.1",8080))
a=input("Enter first number: ")
op=input("Enter operator (+, -, *, /): ")
b=input("Enter second number: ")
client.sendall(f"{a} {op} {b}".encode())
result=client.recv(1024).decode()
print("Result from server:",result)
client.close()

6. UDP SOCKET STRING CONVERSION
Save server as server.py and client as client.py. Run server first.

SERVER (server.py)
import socket
server=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
server.bind(("127.0.0.1",8080))
print("UDP Server waiting for message...")
data,addr=server.recvfrom(1024)
message=data.decode()
result=message.upper()
server.sendto(result.encode(),addr)
print("Converted string:",result)
server.close()

CLIENT (client.py)
import socket
client=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
message=input("Enter a string: ")
client.sendto(message.encode(),("127.0.0.1",8080))
data,addr=client.recvfrom(1024)
print("Uppercase string:",data.decode())
client.close()

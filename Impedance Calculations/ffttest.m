infile = 'f1f81k_tab.txt';
%f5f5 time input output
%f3f1nocap time input output
%f3f1 time output input
data = load(infile, '-ascii');
x = data(:,1); % column 1 of the data text file is assigned the variable x
y = data(:,2); % column 2 is assigned the variable y
z = data(:,3);
yprime = y/sqrt(2);
zprime = z/sqrt(2);
Fs = 194100000;
T = 1/Fs;
Y = fft(z);
Y2= fft(y);
L = 19410;
t = (0:L-1)*T;
P2 = abs (Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);
%f = Fs*(0:(L/2))/L;
P3 = abs (Y2/L);
P4 = P3(1:L/2+1);
P4(2:end-1) = 2*P4(2:end-1);
%{
figure(1)
plot(x,z)
grid on
hold on
%plot (x,y)
hold off


figure (1)
plot(f,P1) 
title('Single-Sided Amplitude Spectrum of Vin')
xlabel('f (Hz)')
ylabel('|P1(f)|')

figure (2)
plot(f,P4) 
title('Single-Sided Amplitude Spectrum of Vout')
xlabel('f (Hz)')
ylabel('|P4(f)|')
%}
%sampling interval (sec)

complex = fft(y)/L; % complex signals
complex2 = fft(z)/L;
f = 0 : Fs/L : Fs/2; % frequency bins
amplitude = 2*abs(complex(1:L/2+1)); % amplitudes
amplitude = amplitude /sqrt(2);
amplitude2 = 2*abs(complex2(1:L/2+1)); % amplitudes
amplitude2 = amplitude2 /sqrt(2);
pow = (amplitude).^2/2*(L/Fs); % power
pow2 = (amplitude2).^2/2*(L/Fs); % power
figure(1);
semilogx(f,20*log10(amplitude),'-b');
grid on;
xlabel('Frequency [Hz]')
ylabel('dB')
figure(2);
semilogx(f,20*log10(amplitude2),'-b');
grid on;
xlabel('Frequency [Hz]')
ylabel('dB')

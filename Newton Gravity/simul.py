import numpy as np
import math
import random
import matplotlib.pyplot as plt
from typing import List, Union

# Valores da tela, para serem usados na criação de bolas e na detecção de colisão com a parede.
SCREEN_WIDTH = 800
SCREEN_HEIGHT = 800

class Ball:
    """
    Representa uma bola com propriedades físicas.
    Esta classe é uma tradução direta da classe Ball em C++.
    """
    def __init__(self, radius: int, mass: float, pos: np.ndarray, vel: np.ndarray):
        self.radius = float(radius)
        self.mass = float(mass) if mass > 0.0001 else 0.0001
        
        self.pos = np.array(pos, dtype=float)
        self.vel = np.array(vel, dtype=float)
        self.acc = np.array([0.0, 0.0])
        self.forces = np.array([0.0, 0.0])

    def apply_force(self, force: np.ndarray):
        """Acumula forças que atuam sobre a bola."""
        self.forces += force

    def reset_force(self):
        """Zera o vetor de forças, chamado a cada frame após a integração."""
        self.forces = np.array([0.0, 0.0])
        
    def integrate(self, dt: float):
        """
        Calcula a nova posição e velocidade com base nas forças aplicadas (Integração de Euler).
        """
        # Evita divisão por zero e valores inválidos
        if np.isnan(self.forces).any():
            self.forces = np.array([0.0, 0.0])

        # a = F / m
        self.acc = self.forces / self.mass
        
        if np.isnan(self.acc).any():
            self.acc = np.array([0.0, 0.0])

        # Atualiza velocidade e posição
        self.vel += self.acc * dt
        self.pos += self.vel * dt
        
        # Reseta as forças para o próximo frame
        self.reset_force()

    def update(self, dt: float):
        """Atualiza o estado da bola, incluindo integração e colisão com as paredes."""
        self.integrate(dt)

        # Colisão com as paredes (lógica idêntica à do C++)
        # Eixo X
        if self.pos[0] + self.radius >= SCREEN_WIDTH:
            self.pos[0] = SCREEN_WIDTH - self.radius
            self.vel[0] *= -1
        elif self.pos[0] - self.radius <= 0:
            self.pos[0] = self.radius
            self.vel[0] *= -1
        
        # Eixo Y
        if self.pos[1] + self.radius >= SCREEN_HEIGHT:
            self.pos[1] = SCREEN_HEIGHT - self.radius
            self.vel[1] *= -1
        elif self.pos[1] - self.radius <= 0:
            self.pos[1] = self.radius
            self.vel[1] *= -1

class Engine:
    """
    Gerencia a simulação, incluindo todas as bolas, interações e atualizações.
    Tradução direta da classe Engine em C++.
    """
    def __init__(self, balls_or_amount: Union[int, List[Ball]]):
        self.G = 10000.0  # Constante gravitacional definida em engine.h
        self.balls: List[Ball] = []

        if isinstance(balls_or_amount, int):
            # Construtor que cria 'amount' bolas aleatórias
            amount = balls_or_amount
            gap = 15
            for _ in range(amount):
                mass = random.randint(30, 60)
                radius = int(mass * 0.3)
                
                pos = np.array([
                    random.randint(radius + gap, SCREEN_WIDTH - radius - gap),
                    random.randint(radius + gap, SCREEN_HEIGHT - radius - gap)
                ])
                vel = np.array([
                    random.randint(-30, 30),
                    random.randint(-30, 30)
                ])
                self.balls.append(Ball(radius, mass, pos, vel))
        elif isinstance(balls_or_amount, list):
            # Construtor que usa uma lista de bolas pré-definida
            self.balls = balls_or_amount

    def compute_velocity_after_collision(self, b1: Ball, b2: Ball) -> tuple[np.ndarray, np.ndarray]:
        pos_diff = b1.pos - b2.pos
        dist_sq = np.dot(pos_diff, pos_diff)

        if dist_sq < 0.0001:
            return b1.vel, b2.vel
        
        normal = pos_diff / math.sqrt(dist_sq)
        tangent = np.array([-normal[1], normal[0]])

        v1n_scalar = np.dot(b1.vel, normal)
        v1t_scalar = np.dot(b1.vel, tangent)
        v2n_scalar = np.dot(b2.vel, normal)
        v2t_scalar = np.dot(b2.vel, tangent)
        
        m1, m2 = b1.mass, b2.mass

        v1n_final_scalar = (v1n_scalar * (m1 - m2) + 2 * m2 * v2n_scalar) / (m1 + m2)
        v2n_final_scalar = (v2n_scalar * (m2 - m1) + 2 * m1 * v1n_scalar) / (m1 + m2)

        v1n_final_vec = normal * v1n_final_scalar
        v2n_final_vec = normal * v2n_final_scalar
        v1t_final_vec = tangent * v1t_scalar
        v2t_final_vec = tangent * v2t_scalar
        
        final_vel1 = v1n_final_vec + v1t_final_vec
        final_vel2 = v2n_final_vec + v2t_final_vec

        return final_vel1, final_vel2

    def update(self, dt: float):
        num_balls = len(self.balls)

        for i in range(num_balls):
            b1 = self.balls[i]
            for j in range(i + 1, num_balls):
                b2 = self.balls[j]
                
                axis = b2.pos - b1.pos
                dist_sq = np.dot(axis, axis)

                if dist_sq < 0.0001:
                    continue

                distance = math.sqrt(dist_sq)
                normal = axis / distance
                radii_sum = b1.radius + b2.radius

                if dist_sq <= (radii_sum ** 2):
                    overlap = radii_sum - distance
                    correction = normal * (overlap / 2.0)
                    b1.pos -= correction
                    b2.pos -= correction

                    new_vel1, new_vel2 = self.compute_velocity_after_collision(b1, b2)
                    b1.vel = new_vel1
                    b2.vel = new_vel2
                else:
                    softening_factor = 1.0
                    m1_dot_m2 = b1.mass * b2.mass
                    
                    scalar_force = self.G * m1_dot_m2 / (dist_sq + softening_factor)
                    
                    force_vec = normal * scalar_force
                    b1.apply_force(force_vec)
                    b2.apply_force(-force_vec)

        for ball in self.balls:
            ball.update(dt)

if __name__ == "__main__":
    ball1 = Ball(radius=15, mass=100.0, pos=np.array([400.0, 400.0]), vel=np.array([0.0, 0.0]))
    ball2 = Ball(radius=15, mass=100.0, pos=np.array([400.0, 200.0]), vel=np.array([0.0, 0.0]))
    ball3 = Ball(radius=15, mass=100.0, pos=np.array([200.0, 400.0]), vel=np.array([0.0, 0.0]))
    
    initial_balls = [ball1, ball2, ball3]
    engine = Engine(initial_balls)
    
    fps = 60
    simulation_seconds = 3
    delta_time = 1.0 / fps
    
    print(f"Iniciando simulação de {simulation_seconds} segundos...")
    
    positions_history = []
    
    for frame in range(fps * simulation_seconds):
        current_positions = [b.pos.copy() for b in engine.balls]
        positions_history.append(current_positions)
        engine.update(delta_time)
        
    print("Simulação concluída. Gerando gráfico...")

    pos_array = np.array(positions_history)
    fig, ax = plt.subplots(figsize=(10, 10))
    
    colors = ['r', 'g', 'b', 'c', 'm', 'y', 'k']
    
    num_balls = pos_array.shape[1]
    for i in range(num_balls):
        x_coords = pos_array[:, i, 0]
        y_coords = pos_array[:, i, 1]
        
        ax.plot(x_coords, y_coords, label=f'Bola {i+1}', color=colors[i % len(colors)])
        ax.plot(x_coords[0], y_coords[0], 'o', color=colors[i % len(colors)], markersize=10, label=f'Início B{i+1}')
        ax.plot(x_coords[-1], y_coords[-1], 'x', color=colors[i % len(colors)], markersize=12, mew=3, label=f'Fim B{i+1}')

    # Configurações do gráfico
    ax.set_title('Trajetória dos Objetos na Simulação')
    ax.set_xlabel('Posição X')
    ax.set_ylabel('Posição Y')
    ax.set_xlim(0, SCREEN_WIDTH)
    ax.set_ylim(0, SCREEN_HEIGHT)
    ax.set_aspect('equal', adjustable='box') 
    ax.grid(True, which='both', linestyle='--', linewidth=0.5)
    ax.legend()
    
    plt.show()
